/* Developer: Eden Wittenberg
 Status: Approved
 Reviewer: NBM
 Group: RD102/ date: 29.8.21
 description: Cpp2C */

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

#define UNUSED(X) ((void)(X))

/*-----------v-table----------------------*/

typedef struct vtable
{
    void (*Dtor)(void *);
    void (*Display)(void *);
    void (*Wash)(void *, int);
} vtable_t;

/*-----------classes----------------------*/

typedef struct PublicTransport
{
    vtable_t *vptr;
    void (*PrintCount)(void);
    int m_license_plate;
} PublicTransport_t;

typedef struct Minibus
{
    PublicTransport_t m_pt;
    int m_numSeats;
} Minibus_t;

typedef struct Taxi
{
    PublicTransport_t m_pt;
} Taxi_t;

typedef struct SpecialTaxi
{
    Taxi_t m_taxi;
} SpecialTaxi_t;

typedef struct PublicConvoy
{
	PublicTransport_t m_pt;

	PublicTransport_t *m_p1;
	PublicTransport_t *m_p2;
	Minibus_t m_m;
	Taxi_t m_t;
} PublicConvoy_t;

/* ---------- funcs declerations --------------*/

void PublicTransportCreate(PublicTransport_t *pt);
void PublicTransportDestroy(void *pt);
void PublicTransportCopyCreate(PublicTransport_t *this, const struct PublicTransport *other);
void PublicTransportDisplay(void *const this);
int PublicTransportGetID(PublicTransport_t *const this);

void MinibusCreate(Minibus_t *mb);
void MinibusDestroy(void *mb);
void MinibusDisplay(void *const this);
void MinibusCopyCreate(Minibus_t *this, const Minibus_t *other);

void Wash(void *this, int minutes);

void TaxiCreate(Taxi_t *taxi);
void TaxiDestroy(void *mb);
void TaxiCopyCreate(Taxi_t *this, const Taxi_t *other);
void TaxiDisplay(void *const this);

void SpecialTaxiCreate(SpecialTaxi_t *taxi);
void SpecialTaxiDestroy(void *taxi);
void SpecialTaxiCopyCreate(SpecialTaxi_t *this, const struct SpecialTaxi *other);
void SpecialTaxiDisplay(void *const this);

void PublicConvoyCreate(PublicConvoy_t * const pt);
void PublicConvoyDestroy(void * const pt);
void PublicConvoyCopyCreate(PublicConvoy_t * const pt, const PublicConvoy_t *other);
void PublicConvoyDisplay(void *const this);

/*-----------static funcs ---------------*/

static void PrintCount();

/* ----------------------- Globals ----------------------*/

static int PublicTransport_s_count = 0;

vtable_t g_public_transport_vtble = {PublicTransportDestroy, PublicTransportDisplay, NULL};
vtable_t g_minibus_vtble = {MinibusDestroy, MinibusDisplay, Wash};
vtable_t g_taxi_vtble = {TaxiDestroy, TaxiDisplay, NULL};
vtable_t g_special_taxi_vtble = {SpecialTaxiDestroy, SpecialTaxiDisplay, NULL};
vtable_t g_public_convoy_vtable = {PublicConvoyDestroy, PublicConvoyDisplay, NULL};
/* ---------- MAX impl --------------*/

int MAX(int a, int b)
{
    return ((a > b) ? a : b);
}

/* ---------- funcs impls --------------*/

void PublicTransportCreate(PublicTransport_t *pt)
{
    pt->vptr = &g_public_transport_vtble;

    ++PublicTransport_s_count;

    pt->m_license_plate = PublicTransport_s_count;

    printf("PublicTransport::Ctor()%d\n", pt->m_license_plate);

    return;
}

void PublicTransportDestroy(void *pt)
{
    --PublicTransport_s_count;

    printf("PublicTransport::Dtor()%d\n", ((PublicTransport_t *)pt)->m_license_plate);

    return;
}

void PublicTransportCopyCreate(PublicTransport_t *this, const struct PublicTransport *other)
{
    UNUSED(other);

    ++PublicTransport_s_count;

    this->m_license_plate = PublicTransport_s_count;
    this->vptr = &g_public_transport_vtble;

    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);

    return;
}

void PublicTransportDisplay(void *const this)
{
    printf("PublicTransport::display(): %d\n", ((PublicTransport_t *)this)->m_license_plate);
}

int PublicTransportGetID(PublicTransport_t *const this)
{
    return (this->m_license_plate);
}

static void PrintCount()
{
    printf("s_count: %d\n", PublicTransport_s_count);

    return;
}

static int GetId(PublicTransport_t *const this)
{
    return (this->m_license_plate);
}

/* ------------------------ Minibus ---------------------*/
void MinibusCreate(Minibus_t *mb)
{
    PublicTransportCreate(&(mb->m_pt));
    mb->m_numSeats = 20;
    mb->m_pt.vptr = &g_minibus_vtble;

    printf("Minibus::Ctor()\n");

    return;
}

void MinibusDestroy(void *mb)
{
    printf("Minibus::Dtor()\n");

    PublicTransportDestroy(&(((Minibus_t *)mb)->m_pt));

    return;
}

void MinibusCopyCreate(Minibus_t *this, const Minibus_t *other)
{
    PublicTransportCopyCreate(&(this->m_pt), &(other->m_pt));
    this->m_pt.vptr = &g_minibus_vtble;
    this->m_numSeats = other->m_numSeats;

    printf("Minibus::CCtor()\n");

    return;
}

void MinibusDisplay(void *const this)
{
    printf("Minibus::display() ID:%d ", GetId(&(((Minibus_t *)this)->m_pt)));
    printf("num seats:%d\n", ((Minibus_t *)this)->m_numSeats);

    return;
}

void Wash(void *this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, GetId(&(((Minibus_t *)this)->m_pt)));

    return;
}

/* ------------------------ Taxi ---------------------------*/

void TaxiCreate(Taxi_t *mb)
{
    PublicTransportCreate(&(mb->m_pt));
    mb->m_pt.vptr = &g_taxi_vtble;

    printf("Taxi::Ctor()\n");

    return;
}

void TaxiDestroy(void *mb)
{
    printf("Taxi::Dtor()\n");

    PublicTransportDestroy(&(((Taxi_t *)mb)->m_pt));

    return;
}

void TaxiCopyCreate(Taxi_t *this, const Taxi_t *other)
{
    PublicTransportCopyCreate(&(this->m_pt), &(((Taxi_t *)other)->m_pt));
    this->m_pt.vptr = &g_taxi_vtble;

    printf("Taxi::CCtor()\n");

    return;
}

void TaxiDisplay(void *const this)
{
    printf("Taxi::display() ID:%d\n", GetId(&(((Minibus_t *)this)->m_pt)));

    return;
}

/* ------------------------ SpecialTaxi ---------------------*/

void SpecialTaxiCreate(SpecialTaxi_t *t)
{
    TaxiCreate(&(t->m_taxi));
    t->m_taxi.m_pt.vptr = &g_special_taxi_vtble;

    printf("SpecialTaxi::Ctor()\n");

    return;
}

void SpecialTaxiDestroy(void *t)
{
    printf("SpecialTaxi::Dtor()\n");

    TaxiDestroy(&(((SpecialTaxi_t *)t)->m_taxi));

    return;
}

void SpecialTaxiCopyCreate(SpecialTaxi_t *this, const SpecialTaxi_t *other)
{
    TaxiCopyCreate(&(this->m_taxi), &(((SpecialTaxi_t *)other)->m_taxi));
    this->m_taxi.m_pt.vptr = &g_special_taxi_vtble;

    printf("SpecialTaxi::CCtor()%d\n", this->m_taxi.m_pt.m_license_plate);

    return;
}

void SpecialTaxiDisplay(void *const this)
{
    printf("SpecialTaxi::display() ID: %d \n", GetId(&(((SpecialTaxi_t *)this)->m_taxi.m_pt)));

    return;
}

/* ------------------------ PublicConvoy ---------------------*/


void PublicConvoyCreate(PublicConvoy_t * const pc)
{
	PublicTransportCreate(&pc->m_pt);

	pc->m_p1 = malloc(sizeof(Minibus_t));
	MinibusCreate((Minibus_t *) pc->m_p1);
	pc->m_p2 = malloc(sizeof(Taxi_t));
	TaxiCreate((Taxi_t *) pc->m_p2);

	MinibusCreate(&pc->m_m);
	TaxiCreate(&pc->m_t);

	pc->m_pt.vptr = &g_public_convoy_vtable;
    printf("PublicConvoy::Ctor()\n");

	return;
}
void PublicConvoyDestroy(void * const pc)
{	

	(((PublicConvoy_t *)pc)->m_p1)->vptr->Dtor((((PublicConvoy_t *)pc)->m_p1));
	(((PublicConvoy_t *)pc)->m_p2)->vptr->Dtor((((PublicConvoy_t *)pc)->m_p2));
	free(((PublicConvoy_t *)pc)->m_p1);
	free(((PublicConvoy_t *)pc)->m_p2);

    printf("PublicConvoy::Dtor()\n");
	TaxiDestroy(&((PublicConvoy_t *)pc)->m_t);
	MinibusDestroy(&((PublicConvoy_t *)pc)->m_m);
	
	PublicTransportDestroy(&((PublicConvoy_t *)pc)->m_pt);

	return;
}
void PublicConvoyCopyCreate(PublicConvoy_t * const pc, const PublicConvoy_t *other)
{
	PublicTransportCopyCreate(&pc->m_pt, &other->m_pt);

	pc->m_p1 = malloc(sizeof(Minibus_t));
	MinibusCopyCreate((Minibus_t *) pc->m_p1, (Minibus_t *) other->m_p1);
	pc->m_p2 = malloc(sizeof(Taxi_t));
	TaxiCopyCreate((Taxi_t *) pc->m_p2, (Taxi_t *) other->m_p2);
	
	MinibusCopyCreate(&pc->m_m, &other->m_m);
	TaxiCopyCreate(&pc->m_t, &other->m_t);

	pc->m_pt.vptr = &g_public_convoy_vtable;
    printf("PublicConvoy::CCtor()\n");

	return;
}
void PublicConvoyDisplay(void *const this)
{
	((PublicConvoy_t *)this)->m_p1->vptr->Display(((PublicConvoy_t *)this)->m_p1);
	((PublicConvoy_t *)this)->m_p2->vptr->Display(((PublicConvoy_t *)this)->m_p2);

	MinibusDisplay(&((PublicConvoy_t *)this)->m_m);
	TaxiDisplay(&((PublicConvoy_t *)this)->m_t);

	return;
}

/* -------------------------PrintInfos-----------------------*/

void PrintInfoPublicTransport(PublicTransport_t *a)
{
    a->vptr->Display(a);

    return;
}

void PrintInfo(void)
{
    PrintCount();

    return;
}

void PrintInfoMinibus(Minibus_t *m)
{
    m->m_pt.vptr->Wash(m, 3);

    return;
}

PublicTransport_t PrintInfoI(int i)
{
    UNUSED(i);
    Minibus_t ret = {0};
    PublicTransport_t pt = {0};
    MinibusCreate(&ret);
    printf("print_info(int i)\n");
    ret.m_pt.vptr->Display(&ret);
    PublicTransportCopyCreate(&pt, &(ret.m_pt));
    ret.m_pt.vptr->Dtor(&ret);

    return (pt);
}




/* --------------------- main ----------------------*/

int main(/* int argc, char **argv, char **envp */)
{
    Minibus_t m; 
    MinibusCreate(&m);
    printf("------------------------------------------------\n");
    PrintInfoMinibus(&m);
    printf("------------------------------------------------\n");

    PublicTransport_t pt_3 = PrintInfoI(3);
    PublicTransportDisplay(&pt_3);
    PublicTransportDestroy(&pt_3);
    printf("------------------------------------------------\n");

    PublicTransport_t *array[3] = {0};

    array[0] = malloc(sizeof(Minibus_t));
    MinibusCreate((Minibus_t *)(*array));

    array[1] = malloc(sizeof(Taxi_t));
    TaxiCreate((Taxi_t *)(*(array + 1)));

    array[2] = malloc(sizeof(Minibus_t));
    MinibusCreate((Minibus_t *)(*(array + 2)));
    printf("------------------------------------------------\n");

    for (int i = 0; i < 3; ++i)
    {
        array[i]->vptr->Display(array[i]);
    }
    printf("------------------------------------------------\n");

    for (int i = 0; i < 3; ++i)
    {
        array[i]->vptr->Dtor(array[i]);
        free(array[i]);
    }
    printf("------------------------------------------------\n");

    PublicTransport_t arr2[3] = {0};

    Minibus_t temp_mb_1;
    MinibusCreate(&temp_mb_1);
    PublicTransportCopyCreate(arr2, &(temp_mb_1.m_pt));
    MinibusDestroy(&temp_mb_1);

    Taxi_t temp_taxi_2;
    TaxiCreate(&temp_taxi_2);
    PublicTransportCopyCreate(arr2 + 1, &(temp_taxi_2.m_pt));
    TaxiDestroy(&temp_taxi_2);

    PublicTransportCreate(arr2 + 2);

    printf("------------------------------------------------\n");

    for (int i = 0; i < 3; ++i)
    {
        PublicTransportDisplay(arr2 + i);
    }
    printf("------------------------------------------------\n");

    PublicTransportDisplay(arr2);
    printf("------------------------------------------------\n");

    PrintCount();

    printf("------------------------------------------------\n");

    Minibus_t m2;
    MinibusCreate(&m2);

    printf("------------------------------------------------\n");

    PrintCount();
    printf("------------------------------------------------\n");

    Minibus_t arr3[4];
    MinibusCreate(arr3);
    MinibusCreate(arr3 + 1);
    MinibusCreate(arr3 + 2);
    MinibusCreate(arr3 + 3);
    printf("------------------------------------------------\n");

    Taxi_t *arr4 = malloc(sizeof(Taxi_t) * 4);
    TaxiCreate(arr4);
    TaxiCreate(arr4 + 1);
    TaxiCreate(arr4 +  2);
    TaxiCreate(arr4 +  3);
    printf("------------------------------------------------\n");

    TaxiDestroy(arr4 + 3);
    TaxiDestroy(arr4 +  2);
    TaxiDestroy(arr4 + 1);
    TaxiDestroy(arr4);
    free(arr4);

    printf("------------------------------------------------\n");

    printf("%d\n", MAX(1, 2));
    printf("------------------------------------------------\n");

    printf("%d\n", MAX(1, (int)2.0f));
    printf("------------------------------------------------\n");

    SpecialTaxi_t st;
    SpecialTaxiCreate(&st);
    printf("------------------------------------------------\n");

    Taxi_t tst;
    TaxiCopyCreate(&tst, &(st.m_taxi));
    TaxiDisplay(&tst);
    TaxiDestroy(&tst);

    printf("------------------------------------------------\n");

	PublicConvoy_t *ts1 = malloc(sizeof(PublicConvoy_t));
	PublicConvoyCreate(ts1);
        printf("------------------------------------------------\n");

	PublicConvoy_t *ts2 = malloc(sizeof(PublicConvoy_t));
	PublicConvoyCopyCreate(ts2, ts1);
    printf("------------------------------------------------\n");

	ts1->m_pt.vptr->Display(ts1);
    printf("------------------------------------------------\n");

	ts2->m_pt.vptr->Display(ts2);
    printf("------------------------------------------------\n");

	PublicConvoyDestroy(ts1); free(ts1);
    printf("------------------------------------------------\n");

	ts2->m_pt.vptr->Display(ts2);
    printf("------------------------------------------------\n");

	PublicConvoyDestroy(ts2); free(ts2);
    printf("------------------------------------------------\n");



    SpecialTaxiDestroy(&st);

    MinibusDestroy(arr3 + 3);
    MinibusDestroy(arr3 + 2);
    MinibusDestroy(arr3 + 1);
    MinibusDestroy(arr3);

    MinibusDestroy(&m2);

    PublicTransportDestroy(arr2 + 2);
    PublicTransportDestroy(arr2 + 1);
    PublicTransportDestroy(arr2);

    MinibusDestroy(&m);

    return 0;
}