using System;
using System.Net;
using System.IO;
using System.Diagnostics;
namespace HttpListenerExample
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                // Create an HTTP listener
                HttpListener listener = new HttpListener();
                listener.Prefixes.Add("http://localhost:8083/");
                listener.Start();

                // Wait for a request
                Console.WriteLine("Waiting for a request...");
                HttpListenerContext context = listener.GetContext();

                // Get the request and parse the message
                HttpListenerRequest request = context.Request;
                string message = new StreamReader(request.InputStream).ReadToEnd();
                Console.WriteLine($"Received message: {message}");
                // Send a response
                HttpListenerResponse response = context.Response;
                string responseString = "ACK";
                byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responseString);
                response.ContentLength64 = buffer.Length;
                Stream output = response.OutputStream;
                output.Write(buffer, 0, buffer.Length);
                output.Close();
                string scriptPath = "/home/elior/Fuzzer/Mutate/Runnables/run.sh";

                // Create a new process
                Process process = new Process();

                // Set the properties of the process
                process.StartInfo.FileName = "bash";
                process.StartInfo.Arguments = scriptPath;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.RedirectStandardOutput = true;

                // Start the process
                process.Start();

                // Read the output of the process
                string output1 = process.StandardOutput.ReadToEnd();

                // Wait for the process to exit
                process.WaitForExit();

                // Print the output
                Console.WriteLine(output1);
                listener.Stop();
            }
        }
    }
}