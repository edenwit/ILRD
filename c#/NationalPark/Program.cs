using System;
using System.Threading;

namespace NationalPark
{
    class Program
    {
        static void Main(string[] args)
        {
            NationalPark park = new NationalPark();

            Single_Traveler t1 = new Single_Traveler("david");
            Single_Traveler t2 = new Single_Traveler("shlomo");
            Single_Traveler t3 = new Single_Traveler("itzik");
            Single_Traveler t4 = new Single_Traveler("yana");

            Family_Traveler f1 = new Family_Traveler("johnson", 3);
            Family_Traveler f2 = new Family_Traveler("levi", 5);

            Group_Traveler g1 = new Group_Traveler("best elders", 10);
            Group_Traveler g2 = new Group_Traveler("most good elders", 30);

            park.CheckIn(t1);
            park.CheckIn(t2);
            park.CheckIn(t3);
            park.CheckIn(t4);
            park.CheckIn(f1);
            park.CheckIn(f2);
            park.CheckIn(g1);
            park.CheckIn(g2);

            for (int i = 0; i < 3; ++i)
            {
                park.CheckStorm();
                Console.WriteLine("-----------------------------------------------");

                Thread.Sleep(5000);
            }

            park.CheckOut(f2);
            park.CheckOut(g1);
            park.CheckOut(t2);
            park.CheckOut(t3);

            for (int i = 0; i < 100; ++i)
            {
                park.CheckStorm();
                Console.WriteLine("-----------------------------------------------");

                Thread.Sleep(5000);
            }
        }
    }
}
