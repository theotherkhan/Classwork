Hasan Khan, hk4cd
Project 2: Disparities & Homographies 
Submitted: Sunday, March 19th (note: extension was given till Sunday, 5:00pm by Professor Barnes)

Instructions: from command line, simply type: python Project1.py

Note: altRMS is the right image

Optimizations:
   
   Gaussian:
             
        Alternating d values: 
        
        RMS value w/d = 8 , colorSigma = 55 , colorSpace = 55 , is:  18.5200713986
        altRMS value w/d = 8 , colorSigma = 55 , colorSpace = 55 , is:  12.1660871144
        
        RMS value w/d =9 , colorSigma = 55, colorSpace = 55 , is: 18.4866500176
        altRMS value w/d = 9 , colorSigma = 55, colorSpace = 55 , is: 11.9967199576
        
        RMS value w/d = 10 , colorSigma = 55 , colorSpace = 55 , is:  18.4866500176
        altRMS value w/d = 10 , colorSigma = 55 , colorSpace = 55 , is:  11.9967199576
         
   
   Bilateral: 
        
        Some sigma color tests:
        
        RMS value w/d = 10 , colorSigma = 55 , colorSpace = 55 , is:  18.63869404
        altRMS value w/d = 10 , colorSigma = 55 , colorSpace = 55 , is:  12.0638250896

        RMS value w/d = 10 , colorSigma = 45 , colorSpace = 55 , is:  18.6386832384
        altRMS value w/d = 10 , colorSigma = 45 , colorSpace = 55 , is:  12.0687701421

        RMS value w/d = 10 , colorSigma = 25 , colorSpace = 55 , is:  18.6385478462
        altRMS value w/d = 10 , colorSigma = 25 , colorSpace = 55 , is:  12.0712264698
    
        RMS value w/d = 10 , colorSigma = 5 , colorSpace = 55 , is:  18.6482136823
        altRMS value w/d = 10 , colorSigma = 5 , colorSpace = 55 , is:  12.1095685596
        
        
        Color sigma = 25 gave lowest error for me.
        
        
        Some space tests:
        
        RMS value w/d = 10 , colorSigma = 25 , colorSpace = 25 , is:  18.6397957044
        altRMS value w/d = 10 , colorSigma = 25 , colorSpace = 25 , is:  12.0738721419

        RMS value w/d = 10 , colorSigma = 25 , colorSpace = 5 , is:  18.6185699897
        altRMS value w/d = 10 , colorSigma = 25 , colorSpace = 5 , is:  12.0529452574
        
        RMS value w/d = 10 , colorSigma = 25 , colorSpace = 1 , is:  18.6167011498
        altRMS value w/d = 10 , colorSigma = 25 , colorSpace = 1 , is:  11.6392746917

        Space = 1 gave lowest error for me.
           
    Homographies:
    
    The best homography matrix (which corresponds with the included warped image) is:
    
    [[  3.30000000e-01  -6.30000000e-01   3.88560000e+02]
     [ -9.00000000e-02  -5.00000000e-02   1.93240000e+02]
     [ -0.00000000e+00  -0.00000000e+00   1.00000000e+00]]
     
     
    