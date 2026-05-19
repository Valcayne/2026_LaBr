# Monitor v1.0.0

Program to monitor the Er and U campaing!

## Build

The programs use `CMake` as its build system. To compile it:

```sh
cd build
cmake ..
cmake --build . --config Release --target all -- -j 10
cd ..
```

These commands create a `Monitor` executable on the [`bin`](bin) folder and keep all the build artifacts on the [`build`](build) folder.

## Run

To launch the program, execute the binary passing a the name of the runs proceesed configuration file:

```sh
bin/Monitor "AllRuns"
```

## Results

The program creates a `Monitoring.root` file with graphs that are useful to check that the experiment is running correctly! 📈


## Condor CERN

To launch programs on Condor
```sh
condor_submit LaunchMonitor.sh 
```
The runs to be launched are in:

```sh
Monitor/Condor/Arguments.txt
```



EmilioRuns


To draw histograms from terminal 

```c++
// Acceder al directorio "Dedicated/C6D6"
TDirectory *dir = (TDirectory*) _file0->Get("Dedicated/C6D6");

// Obtener el canvas específico
TCanvas *c = (TCanvas*) dir->Get("C6D6 4 counts per proton (1)");

if (c) {
    c->Draw();
} else {
    cout << "No se encontró el canvas" << endl;
}```
