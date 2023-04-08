mcs /home/elior/Fuzzer/Mutate/ProtocolParser/AddProtocol.cs
mono /home/elior/Fuzzer/Mutate/ProtocolParser/AddProtocol.exe
echo "Added the protocol"
gcc /home/elior/Fuzzer/Mutate/VmCommunication/client.c -o cl
./cl
gcc /home/elior/Fuzzer/Mutate/Fuzzing/fuzz.c -o testing
timeout 15s ./testing