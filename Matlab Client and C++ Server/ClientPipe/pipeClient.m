NET.addAssembly('System.Core');
MypipeClient  = System.IO.Pipes.NamedPipeClientStream(".",'my_pipe',...
    System.IO.Pipes.PipeDirection.InOut,...
    System.IO.Pipes.PipeOptions.Asynchronous);

if MypipeClient.IsConnected ~= true
    MypipeClient.Connect(2000);
    disp('Matlab Piped Client is connected with C++ Piped Server');
    disp('Reading dataStream...')
    sr = System.IO.StreamReader(MypipeClient);
    %sw = System.IO.StreamWriter('E:/pipeKo.txt')
    k=0;
    while (true)
        line = sr.ReadLine();
        if(isempty(line))
            break;
        else
            time = datestr(now);
            disp(time);
            disp(line);
        end
             
        %sw.WriteLine(time);
        %sw.WriteLine(line);
        %sw.Flush();
        %pause(1);
        k=k+1;
    end
    %sw.Close();   
end

Close(MypipeClient);

         
            
%while (line)
    %System.IO.File.WriteAllText('E:/pipe.txt','test');
    %Systen.Console.WriteLine(sr.ReadLine());
    %sw.WriteLine(sr.ReadLine());
    %sw.WriteLine('1');
    %disp(1);
    %disp(sr.ReadLine());
    %line = sr.ReadLine();
%end
%System.Console.WriteLine('Finished');     
%sw.WriteLine('Finished');
%sw.Flush();

