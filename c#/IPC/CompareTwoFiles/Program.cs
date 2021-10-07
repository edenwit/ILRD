using System;
using System.IO;
using System.Linq;

using System.Collections.Generic;

namespace CompareTwoFiles
{
    class Program
    {
        static void Main(string[] args)
        {
            var file1Lines = File.ReadLines(args[0]);
            var file2Lines = File.ReadLines(args[1]);
            IEnumerable<String> inFirstNotInSecond = file1Lines.Except(file2Lines);
            IEnumerable<String> inSecondNotInFirst = file2Lines.Except(file1Lines);

            if (!inFirstNotInSecond.Any() && !inSecondNotInFirst.Any())
            {
                Console.WriteLine("files are identical.");
            }
            else
            {
                Console.WriteLine("Lines in \n'{0}'\n and not in \n'{1}':", args[0], args[1]);
                Console.WriteLine("-------------------------------------------------");
                foreach (String line in inFirstNotInSecond)
                {
                    Console.WriteLine(line);
                }
                Console.WriteLine("-------------------------------------------------");


                Console.WriteLine("Lines in \n'{0}'\n and not in \n'{1}':", args[1], args[0]);
                Console.WriteLine("-------------------------------------------------");


                foreach (String line in inSecondNotInFirst)
                {
                    Console.WriteLine(line);
                }
                Console.WriteLine("-------------------------------------------------");


            }

        }
    }
}
