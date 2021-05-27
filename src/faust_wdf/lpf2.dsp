import("stdfaust.lib");

second_order(f0, Vin) = wd.buildtree(connectionTree)
with{
    
    //declare nodes
    r1(i) = wd.resistor(i, R1);
    r2(i) = wd.resistor(i, R2);
    c1(i) = wd.capacitor(i, C1);
    c2(i) = wd.capacitor_Vout(i, C2);
    vin(i) = wd.u_voltage(i, Vin);
    
    //declare tree
    connectionTree = vin : wd.series : (r1, (wd.parallel : (c1, (wd.series: (r2, c2)))));

    R2 = R1; 
    R1 = 1*10^3; 

    C2 = C1; 
    C1 = 1/f0*1.62*10^-4; 
};

process = second_order(1000); 