% Developed By Ashadullah Shawon
% Software Engineer, FSMB
% Email: shawona@frontiersemi.com

NET.addAssembly('System.Core');
MypipeServer  = System.IO.Pipes.NamedPipeServerStream('my_pipe', ...
                System.IO.Pipes.PipeDirection.InOut, ...
                System.IO.Pipes.NamedPipeServerStream.MaxAllowedServerInstances,...
                System.IO.Pipes.PipeTransmissionMode.Byte,...
System.IO.Pipes.PipeOptions.Asynchronous);

disp("Waiting for client connection...");
MypipeServer.WaitForConnection();
disp("Client Connected");
sw = System.IO.StreamWriter(MypipeServer);
%sw.AutoFlush = true;
time = datestr(now);
disp(time);
disp("Server: Hello");
sw.WriteLine("Hello");
sw.Flush();
pause(5);
sx = System.IO.StreamWriter(MypipeServer);
time2 = datestr(now);
disp(time2);
disp("Server: Run The FPD Measurement Software");
sx.WriteLine("Run The FPD Measurement Software");
sx.Flush();
pause(5);
sy = System.IO.StreamWriter(MypipeServer);
time3 = datestr(now);
disp(time3);
disp("Server: Calculate The Result");
sy.WriteLine("Calculate The Result");
sy.Flush();
sz = System.IO.StreamWriter(MypipeServer);
sz.WriteLine("0");
sz.Flush();