using System;
using System.Collections.Generic;
using System.IO;

namespace Grundlagen
{
    class Program
    {
        static void Main(string[] args)
        {

            string fileName = @"C:\Users\ivayl\Desktop\5.Semester\ApplicationEntwiclung-C#\Day11.txt";

            IEnumerable<string> lines = File.ReadLines(fileName);
            // Console.WriteLine(String.Join(Environment.NewLine, lines));
            List<string[]> wörter = new List<string[]>();

            List<string> wörterZuSpeichern = new List<string>();

            List<int> wörter_anzahl = new List<int>();

            List<string> uniqueList = new List<string>();



            int count = 0;

            foreach (string s in lines)
            {

                String[] strlist = s.Split('-', 2, StringSplitOptions.RemoveEmptyEntries);
                wörter.Add(strlist);
                if(!uniqueList.Contains(strlist[0]))
                {
                    uniqueList.Add(strlist[0]);

                }


                if (!uniqueList.Contains(strlist[1]))
                {
                    uniqueList.Add(strlist[1]);

                }

            }






            int i = 0;

            while (uniqueList[i] != "end")
            {
                int sum = 0;
                foreach (string d in lines)
                {
                    //Console.WriteLine("D:"+d);
                    //Console.WriteLine("uniqueList:" + uniqueList[i]);

                    if (d.Contains(uniqueList[i]))
                    {
                        sum++;

                    }


                }

                wörterZuSpeichern.Add(uniqueList[i]);
                wörter_anzahl.Add(sum);

                i++;
            }

            int final = 1;


 


            for(int d=0;d< wörter_anzahl.Count;d++  ) 
            {

             

                Console.WriteLine(wörter_anzahl[d]);
                final *= wörter_anzahl[d];

            }

            Console.WriteLine(final);
        }
    }
}
