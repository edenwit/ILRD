using Microsoft.VisualStudio.TestTools.UnitTesting;
using WS3;
using System;

namespace TestShape
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {

            Circle c1 = new Circle();
            Circle c2 = new Circle(5, "yellow", false);
            Rectangle r1 = new Rectangle();
            Rectangle r2 = new Rectangle("blue", true, 4, 5);

            c1.ToString();
            c2.ToString();
            r1.ToString();
            r2.ToString();
            Console.WriteLine("----------------------------------------------");

            ComplexShape cs = new ComplexShape();
            cs.Add(c1);
            cs.Display();
            Console.WriteLine("collection " + nameof(cs) + " perimeter: " + cs.Perimeter() + ", area: " + cs.Area());
            Console.WriteLine("----------------------------------------------");
            cs.Add(c1);
            cs.Add(c2);
            cs.Add(r1);
            cs.Add(r2);
            cs.Display();
            Console.WriteLine("collection " + nameof(cs) + " perimeter: " + cs.Perimeter() + ", area: " + cs.Area());



        }
    }
}
