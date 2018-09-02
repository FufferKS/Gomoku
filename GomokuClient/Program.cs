using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

using GomokuServer;

namespace GomokuClient
{
    class Program
    {
        static void Main(string[] args)
        {
            IGomokuServerRoom room;
            IGUI gui;
            gui = new ConsoleGUI();
            room = new GomokuServerRoom();
            Klient klient = new Klient((GomokuServerRoom)room, (ConsoleGUI)gui);
            klient.Play();
            Console.WriteLine("Game finished, press anything to continue");
            Console.ReadKey();
        }
           
    }
}
