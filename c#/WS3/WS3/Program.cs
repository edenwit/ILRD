using System;
using System.Collections.Generic;

namespace WS3
{
    public abstract class Shape
    {
        private bool m_is_filled;
        private string m_color;

        public Shape()
        {
            m_is_filled = true;
            m_color = "green";
        }
        public Shape(string color, bool is_filled)
        {
            m_is_filled = is_filled;
            m_color = color;
        }

        public virtual double Area();
        public virtual double Perimeter();

        public override string ToString()
        {
            if (m_is_filled)
            {
                return "A Shape with color of "+ m_color + " and filled";
            }
            
            return "A Shape with color of " + m_color + " and not filled";
        }

    }

    public class Circle : Shape
    {

        public Circle(double radius = 1.0)
        {
            m_radius = radius;
        }

        public Circle(double radius, string color, bool is_filled) : base(color, is_filled)
        {
            m_radius = radius;
        }

        public override string ToString()
        {
            return "A Circle with radius = " + m_radius + ", which is derived class of " + base.ToString();
        }
        public override double Area()
        {
            return (Math.Pow(m_radius, 2) * Math.PI);
        }
        public override double Perimeter()
        {
            return ((m_radius * 2) * Math.PI);
        }

        private double m_radius;

    }

    public class Rectangle : Shape
    {

        static Rectangle()
        {
            Console.WriteLine("A Rectangle class initialized!");
        }
        public Rectangle(double width = 1.0, double length = 1.0)
        {
            m_width = width;
            m_length = length;
        }
        public Rectangle(string color, bool is_filled, double width, double length) : base(color, is_filled)
        {
            m_width = width;
            m_length = length;
        }
        public override string ToString()
        {
            return "A Rectangle with width = " + m_width + " and length = " + m_length + ", which is derived class of " + base.ToString();
        }
        public override double Area()
        {
            return m_length * m_width;
        }
        public override double Perimeter()
        {

            return (m_length + m_width) * 2;
        }

        private double m_width;
        private double m_length;
    }
    public class ComplexShape : Shape
    {
        private List<Shape> shapes_collection = new List<Shape>();

        public ComplexShape()
        {
            Console.WriteLine("An instance of ComplexShape was initialized.");
        }


        public void Add(Shape shp)
        {
            shapes_collection.Add(shp);
        }

        public void Display()
        {
            foreach(Shape sh in shapes_collection)
            {
                Console.WriteLine(sh.ToString());
            }
        }
        public override double Area()
        {
            double area_sum = 0;

            foreach (Shape sh in shapes_collection)
            {
                area_sum += sh.Area();
            }

            return area_sum;
        }
        public override double Perimeter()
        {
            double perimeter_sum = 0;

            foreach (Shape sh in shapes_collection)
            {
                perimeter_sum += sh.Perimeter();
            }

            return perimeter_sum;
        }
    }




    class Program
    {
        static void Main(string[] args)
        {
            
        }
    }
}


