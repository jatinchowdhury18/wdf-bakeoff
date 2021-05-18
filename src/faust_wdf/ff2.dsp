import("stdfaust.lib");

wdf = library("../../modules/faust-wdf-library/wdmodels.lib");

// set up components
Vin(x) = wdf.u_voltage(x, _);
Vbias(x) = wdf.resVoltage(x, 0.001, 4.5);

R5(x) = wdf.resistor(x, 5100.0);
R8(x) = wdf.resistor(x, 1500.0);
R9(x) = wdf.resistor(x, 1000.0);
RVTop(x) = wdf.resistor(x, 50000.0);
RVBot(x) = wdf.resistor(x, 50000.0);
R15(x) = wdf.resistor(x, 22000.0);
R16(x) = wdf.resistor_output_current(x, 47000.0);
R17(x) = wdf.resistor(x, 27000.0);
R18(x) = wdf.resistor(x, 12000.0);

C4(x) = wdf.capacitor(x, 68*(10^-9));
C6(x) = wdf.capacitor(x, 390*(10^-9));
C11(x) = wdf.capacitor(x, 2.2*(10^-9));
C12(x) = wdf.capacitor(x, 27*(10^-9));

S1 = wdf.series : (C12, R18);
P1 = wdf.parallel : (S1, R17);
S2 = wdf.series : (C11, R15);
S3 = wdf.series : (S2, R16);
P2 = wdf.parallel : (S3, P1);
P3 = wdf.parallel : (P2, RVBot);
S4 = wdf.series : (P3, RVTop);
S5 = wdf.series : (C6, R9);
P4 = wdf.parallel : (S4, S5);
P5 = wdf.parallel : (P4, R8);
S6 = wdf.series : (P5, Vbias);
P6 = wdf.parallel : (R5, C4);
S7 = wdf.series : (P6, S6);
// polarity inverter?
tree = Vin : S7;

ff2_in = (_, ro.crossn1(6) : wdf.builddown(tree))~wdf.buildup(tree) : wdf.buildout(tree);

process = ff2_in;
