# 19/04/2024 LABR and LACL parameters changed with pulse shape fitting
# 26/04/2024 LIGL added

.                                                DETECTOR SPECIFIC PARAMETERS (Lines may be commented with '#' sign!)
===================================================================================================================================================================================================================================
DETECTOR   DETECTOR   DETECTOR  STEP   TIMING    MIXED     EXPAND   SMOOTHING  TIME     G-FLASH    G-FLASH     G-FLASH     G-FLASH   BASELINE   BASELINE   AMPLITUDE   AMPLITUDE   AREA/AMP.   AREA/AMP.   SIGNAL WIDTH   SIGNAL WIDTH    NUMBER OF     PULSE SHAPE
  NAME      NUMBER     CLASS    SIZE   FILTER   POLARITY   PULSES    FILTER    LIMIT    OPTION    THRESHOLD    MIN_WIDTH   WINDOW     OPTION     FILTER     OPTION     THRESHOLD   LOW THR.    HIGH THR.   LOW THR.       HIGH THR.      PULSE SHAPES     ADDRESS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PKUP        0           PSA     300/6     0        0          3        50      100000      0          2000         1         0          -1         300         0          2000       0.0        2000          1             4000              0

###################

SILI        1           PSA      500      0        0          0         0      12e3/1e9    0        30000.         0.        0         0/70        3e4         1           500       300        2000         500            4000              0
SILI        2           PSA      500      0        0          0         0      12e3/1e9    0        30000.         0.        0         0/70        3e4         1           500       300        2000         500            4000              0
SILI        3           PSA      500      0        0          0         0      12e3/1e9    0        30000.         0.        0         0/70        3e4         1           500       300        2000         500            4000              0
SILI        4           PSA      500      0        0          0         0      12e3/1e9    0        30000.         0.        0         0/70        3e4         1           500       300        2000         500            4000              0

###################

C6D6        1           PSA      8/3       0        0          0         0      12e3/1E9    1        50000.       50/20       0           0        200/0        1            70       1.0        9000          2              300              0
C6D6        2           PSA      8/3       0        0          0         0      12e3/1E9    1        50000.       50/20       0           0        200/0        1            75       1.0        9000          2              300              0
C6D6        3           PSA      8/3       0        0          0         0      12e3/1E9    1        50000.       50/20       0           0        200/0        1            70       1.0        9000          2              300              0
C6D6        4           PSA      8/3       0        0          0         0      12e3/1E9    1        50000.       50/20       0           0        200/0        1            75       1.0        9000          2              300              0.
#LIGL          0       PSA   200/6     0        0         0         0       1e9      0       10000.0       100.        0          1        3000         0          50         0.0         2e9           1             5000            0


#LABR           1        PSA      7/0.5          0        0         0      0    12e3/30e3      0      30000.       50       30e3    6/100      1000/100        2          100         1.0         9000          10/30           2000      2  /afs/cern.ch/work/a/adcasano/public/processing/labr_ear1/labr_shape_y88_116391_low.dat /afs/cern.ch/work/a/adcasano/public/processing/labr_ear1/labr_shape_y88_116391_high.dat


LABR          0          PSA     30/6        0        0          0         0        1e9       0         10000.       50         30e3       1         500      2          200         1.0        9000        10/30           2000              1 /eos/experiment/ntof/repositories/RAW2ROOT/UserInput/2024/f_Shape_LABR_1_Amp10_10000_v1_neg.dat
LABR          5          PSA     30/6        0        0          0         0        1e9       0         10000.       50         30e3       1         500      2          200         1.0        9000        10/30           2000              1 /eos/experiment/ntof/repositories/RAW2ROOT/UserInput/2024/f_Shape_LABR_5_Amp10_10000_v1_neg.dat
LACL          1          PSA     30/6        0        0          0         0        1e9       0         10000.       50         30e3       1         700      0          200         1.0        9000        10/30           2000              0
LIGL          0          PSA     30/6        0        0          0       100        1e9       0         10000.       50.        0          1        3000      0          200        10.0         2e9           30           5000              0
