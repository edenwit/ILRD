using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NationalPark
{

    public class MyArgs : EventArgs
    {
        public int Args { get; set; }
    }

class NationalPark
    {
        public NationalPark(string name = "jew park")
        {
            weather_center = new WeatherCenter();
            park_name = name;

            Console.WriteLine("National Park {0} created.", park_name);
        }

        public void CheckIn(Park_Traveler tr)
        {
            Travelers.Add(tr);
            Console.WriteLine("Traveler:" + tr.Display() + "checked in.");

            //StormComing += tr.Behave();
        }


        public void CheckOut(Park_Traveler tr)
        {
            Travelers.Remove(tr);
            Console.WriteLine("Traveler:" + tr.Display() + "checked out.");

        }

        public void CheckStorm()
        {
            int storm_intensity = weather_center.CheckForStorm();

            if (3 <= storm_intensity)
            {
                foreach (Park_Traveler Traveler in Travelers)
                {
                    MyArgs currArgs = new MyArgs();
                    currArgs.Args = storm_intensity;
                    Traveler.StormResponse.Invoke(this, currArgs);
                }

                //StormComing.Invoke();
            }
        }

        private WeatherCenter weather_center;
        private string park_name;
        private List<Park_Traveler> Travelers = new List<Park_Traveler>();


    }
}
