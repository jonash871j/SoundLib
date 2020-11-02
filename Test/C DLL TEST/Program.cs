using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("SoundLib API.dll")]
    static extern short SetSomething(int x);

    static void Main(string[] args)
    {
        Console.WriteLine("This is C# calling from a C libary!");
        SetSomething(1234);
    }
}