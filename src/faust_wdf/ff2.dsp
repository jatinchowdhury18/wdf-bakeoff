import("stdfaust.lib");

ff2(in1) = wd.buildtree(tree)
with{
    // set up components
    Vin(x) = wd.u_voltage(x, _);
    Vbias(x) = wd.resVoltage(x, 0.001, 4.5);

    R5(x) = wd.resistor(x, 5100.0);
    R8(x) = wd.resistor(x, 1500.0);
    R9(x) = wd.resistor(x, 1000.0);
    RVTop(x) = wd.resistor(x, 50000.0);
    RVBot(x) = wd.resistor(x, 50000.0);
    R15(x) = wd.resistor(x, 22000.0);
    R16(x) = wd.resistor_Iout(x, 47000.0);
    R17(x) = wd.resistor(x, 27000.0);
    R18(x) = wd.resistor(x, 12000.0);

    C4(x) = wd.capacitor(x, 68*(10^-9));
    C6(x) = wd.capacitor(x, 390*(10^-9));
    C11(x) = wd.capacitor(x, 2.2*(10^-9));
    C12(x) = wd.capacitor(x, 27*(10^-9));

    // declare tree

    S1 = wd.series : (C12, R18);
    P1 = wd.parallel : (S1, R17);
    S2 = wd.series : (C11, R15);
    S3 = wd.series : (S2, R16);
    P2 = wd.parallel : (S3, P1);
    P3 = wd.parallel : (P2, RVBot);
    S4 = wd.series : (P3, RVTop);
    S5 = wd.series : (C6, R9);
    P4 = wd.parallel : (S4, S5);
    P5 = wd.parallel : (P4, R8);
    S6 = wd.series : (P5, Vbias);
    P6 = wd.parallel : (R5, C4);
    S7 = wd.series : (P6, S6);

    // where does polarity inverter need to go?
    tree = Vin : S7;
};

process = ff2;
