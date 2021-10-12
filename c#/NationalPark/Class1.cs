using System;

namespace NationalPark
{
    class WeatherCenter
    {
        public int GetWeather()
        {
            Random rand = new Random();
            int storm_intensity = rand.Next(0, 11);

            return storm_intensity;
        }

        public int CheckForStorm()
        {
            int storm_intensity = GetWeather();

            if (3 <= storm_intensity)
            {
                Console.WriteLine("Storm level {0}", storm_intensity);
                //StormComing.Invoke();
            }

            return storm_intensity;
        }

    }
}
