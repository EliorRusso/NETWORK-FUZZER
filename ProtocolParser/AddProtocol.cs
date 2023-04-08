using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
namespace WritingToATextFile
{
    
    class Program
    {
        private static void Main(string[] args)
        {
            List<String> infoarray = new List<String>();
            using(StreamReader file = new StreamReader("/home/elior/Fuzzer/Mutate/WebInfo/InfoForProtocol.txt")) {  
            int counter = 0;  
            string ln;  
            
            while ((ln = file.ReadLine()) != null) {  
                infoarray.Add(ln);
                Console.WriteLine(infoarray[counter]);  
                counter++;  
            }  
            file.Close(); 
            } 
            String prot =  "typedef union protocol{";
            String type = "short int ";
            using (var sw = new StreamWriter("/home/elior/Fuzzer/Mutate/WebInfo/AddProtocol.h"))
            {
                    //sw.WriteLine("#include <stdint.h>");
                    sw.WriteLine(prot);
            //Console.WriteLine("Please state the name of the protocol");
            String ProtName = infoarray[1];
            Console.WriteLine(ProtName);
            //Console.WriteLine("Please state the number of fields");
            int NumberOfFields = Convert.ToInt32(infoarray[2]);
            Console.WriteLine(NumberOfFields);
            String[] fields = new String[20];
            int[] sizes = new int[NumberOfFields];
            int indexarr = 0;
            for(int i = 3; i <= NumberOfFields * 4 + 3;i+=4){
                String fieldinput = infoarray[i];
                Console.WriteLine(fieldinput);
                //int sizeinput = Convert.ToInt32(infoarray[i+1]);
                //Console.WriteLine(sizeinput);
                fields[indexarr] = fieldinput;
                //sizes[indexarr] = sizeinput;
                indexarr++;
            }
            indexarr = 0;
             for(int i = 4; i <= NumberOfFields * 4 ;i+=4){
                // String fieldinput = infoarray[i];
                // Console.WriteLine(fieldinput);
                int sizeinput = Convert.ToInt32(infoarray[i]);
                Console.WriteLine(sizeinput);
                //Console.WriteLine(sizeinput);
                sizes[indexarr] = sizeinput;
                //sizes[indexarr] = sizeinput;
                indexarr++;
            }
            int maxElement = sizes[0];
            for (int index = 1; index < sizes.Length; index++)
            {
                if (sizes[index] > maxElement)
                    maxElement = sizes[index];
            }
            Console.WriteLine(maxElement);
            if(maxElement < 8){
                type =  "uint8_t ";
            }
            if(maxElement > 8 && maxElement <= 16){
                type = "uint16_t ";
            }
            if(maxElement >  16 && maxElement <= 32){
                type = "uint32_t ";
            }
            if(maxElement > 32 && maxElement <= 64){
                type = "uint64_t ";
            }
            String structname = "struct " + ProtName + '{';
            sw.WriteLine(structname);
            for(int i = 0; i < NumberOfFields; i++){
                String fieldoutput = type + fields[i] + ':' + sizes[i] + ';';
                sw.WriteLine(fieldoutput);
            }
            String fieldarray = "}; " + type + "array[" + NumberOfFields + "];";
            sw.WriteLine(fieldarray);
            sw.WriteLine("};");
            String sizearrfile = "int s[" + NumberOfFields + "] = {";
            sizearrfile = sizearrfile + sizes[0];
            for(int i = 1; i < NumberOfFields; i++){
                sizearrfile = sizearrfile + ',';
                sizearrfile = sizearrfile + sizes[i];
            }
            sizearrfile = sizearrfile + "};";
            sw.WriteLine(sizearrfile);
            String FieldsNumber = "int num = " + NumberOfFields + ';';
            sw.WriteLine(FieldsNumber);
            }
        }
    }
}