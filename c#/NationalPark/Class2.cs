using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NationalPark
{
    public abstract class Park_Traveler
    {
        public EventHandler<MyArgs> StormResponse;

        public Park_Traveler(string type, string name)
        {
            traveler_type = type;
            traveler_name = name;

        }
        public string Display()
        {
            return ("Traveler type: " + traveler_type + ", name: " + traveler_name  + ".");
        }

        //public abstract void Behave(int intensity);

        private string traveler_type;
        private string traveler_name;
    }

    public class Single_Traveler : Park_Traveler
    {

        public Single_Traveler(string name) : base("single", name)
        {
            StormResponse += (s, args) =>
            {
                if (args.Args == 10)
                {
                    Console.WriteLine(Display() + "Single traveler quits only at 10!.");
                }
                else
                {
                    Console.WriteLine(Display() + "Single traveler will never yield!");
                }
            };
        }

    }

    public class Family_Traveler : Park_Traveler
    {

        public Family_Traveler(string name, int num_of_members = 5) : base("family", name)
        {
            members = new List<Park_Traveler>();

            for (int i = 0; i < num_of_members; ++i)
            {
                members.Add(new Single_Traveler("family member " + (i + 1)));
            }

            StormResponse += (s, args) =>
            {
                Display();
                if (args.Args >= 6)
                {
                    Console.WriteLine(Display() + "We as a family can't take the risk.");
                }
                else
                {
                    Console.WriteLine(Display() + "Strong family strong country!");
                }
            };
        }

        private List<Park_Traveler> members;
    }

    public class Group_Traveler : Park_Traveler
    {
        public Group_Traveler(string name, int num_of_members = 5) : base("group", name)
        {
            members = new List<Park_Traveler>();

            for (int i = 0; i < num_of_members; ++i)
            {
                members.Add(new Single_Traveler("group member " + (i + 1)));
            }

            StormResponse += (s, args) =>
            {
                Display();
                if (args.Args == 10)
                {
                    Console.WriteLine(Display() + "This group is gonna die!!");
                }
                else if (args.Args >= 7)
                {
                    Console.WriteLine(Display() + "Some of us are not gonna make it!");
                }
                else if (args.Args >= 5)
                {
                    Console.WriteLine(Display() + "only Suzan will suffer!");
                }
                else
                {
                    Console.WriteLine(Display() + "That's nothing for this group!!");
                }
            };
        }

        private List<Park_Traveler> members;
    }


}
