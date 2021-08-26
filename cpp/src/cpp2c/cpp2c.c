#include <stdio.h>
#include <stdlib.h>

#define UNUSED(X) ((void)(X))
/*-----------static funcs ---------------*/

static void PrintCount();

/*-----------v-table----------------------*/

typedef struct vtable
{
    void (*Dtor)(void*);
    void (*Display)(void*);
    void (*Wash)(void*, int);
} vtable_t;

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



/* ---------- funcs declerations --------------*/
void PublicTransportCreate(PublicTransport_t *pt);
void PublicTransportDestroy(void *pt);
void PublicTransportCopyCreate(PublicTransport_t *this, const struct PublicTransport *other);
void PublicTransportDisplay(void *const this);
int PublicTransportGetID(PublicTransport_t * const this);

void MinibusCreate(Minibus_t *mb);
void MinibusDestroy(void *mb);
void MinibusDisplay(void* const this);
void MinibusCopyCreate(Minibus_t *this, const Minibus_t *other);


void Wash(void *this, int minutes);

void TaxiCreate(Taxi_t *taxi);
void TaxiDestroy(void *mb);
void TaxiCopyCreate(Taxi_t *this, const Taxi_t *other);
void TaxiDisplay(void* const this);

void SpecialTaxiCreate(SpecialTaxi_t *taxi);
void SpecialTaxiDestroy(void *taxi);
void SpecialTaxiCopyCreate(SpecialTaxi_t *this, const struct SpecialTaxi *other);
void SpecialTaxiDisplay(void * const this);

/* ----------------------- Globals ----------------------*/

static int PublicTransport_s_count = 0;

vtable_t g_public_transport_vtble
    = {PublicTransportDestroy, PublicTransportDisplay, NULL};
vtable_t g_minibus_vtble 
    = {MinibusDestroy, MinibusDisplay, Wash};
vtable_t g_taxi_vtble 
    = {TaxiDestroy, TaxiDisplay, NULL};
vtable_t g_special_taxi_vtble 
    = {SpecialTaxiDestroy, SpecialTaxiDisplay, NULL};

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

int PublicTransportGetID(PublicTransport_t * const this)
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

	printf("Minibus::CCtor()%d\n", this->m_pt.m_license_plate);

	return ;
}

void MinibusDisplay(void* const this)
{
	printf("Minibus::display() ID:%d ", GetId(&(((Minibus_t*)this)->m_pt)));
    printf("num seats:%d\n", ((Minibus_t*)this)->m_numSeats);

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

void TaxiDisplay(void* const this)
{
	printf("Taxi::display() ID:%d\n", GetId(&(((Minibus_t*)this)->m_pt)));

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

void SpecialTaxiDisplay(void* const this)
{
	printf("SpecialTaxi::display() ID: %d \n", GetId(&(((SpecialTaxi_t*)this)->m_taxi.m_pt)));

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

    for (int i = 0; i < 3; ++i) {
        array[i]->vptr->Display(array[i]);
    }
    printf("------------------------------------------------\n");

    for (int i = 0; i < 3; ++i) {
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

    PrintInfo();

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
 	TaxiCreate(arr4 + sizeof(Taxi_t) * 1);
 	TaxiCreate(arr4 + sizeof(Taxi_t) * 2);
 	TaxiCreate(arr4 + sizeof(Taxi_t) * 3);
    printf("------------------------------------------------\n");


	TaxiDestroy(arr4 + sizeof(Taxi_t) * 3);
	TaxiDestroy(arr4 + sizeof(Taxi_t) * 2);
	TaxiDestroy(arr4 + sizeof(Taxi_t) * 1);
	TaxiDestroy(arr4);
    free(arr4);
    
    printf("------------------------------------------------\n");

	printf("%d\n", MAX(1,2));
    printf("------------------------------------------------\n");

	printf("%d\n", MAX(1,(int)2.0f));
    printf("------------------------------------------------\n");


    SpecialTaxi_t st;
	SpecialTaxiCreate(&st);
    printf("------------------------------------------------\n");

    Taxi_t tst;
    TaxiCopyCreate(&tst, &(st.m_taxi));
    TaxiDisplay(&tst);
    TaxiDestroy(&tst);

    printf("------------------------------------------------\n");

    /*
    PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2;*/

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