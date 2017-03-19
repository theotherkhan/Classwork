# Hasan Khan, hk4cd
# Project 2: Disparities & Homographies 
# Submitted: Sunday, March 19th (note: extension was given till Sunday, 5:00pm by Professor Barnes) 


import random
import numpy as np, skimage, skimage.io, pylab, skimage.filters, scipy, scipy.signal 
import matplotlib.pyplot as plt
import cv2

# Part 1: DISPARATIES----------------------------------------------------------------------------------------------------------------



# Importing flower images

src1=skimage.io.imread('/Users/Hasan/Desktop/Workspace/Computer_Vision/Project2/im0.png')
src2=skimage.io.imread('/Users/Hasan/Desktop/Workspace/Computer_Vision/Project2/im1.png')

R=skimage.img_as_float(src1) 
L=skimage.img_as_float(src2)

dLimit = L.shape[0]/3



# Calculating disparaties

import math 
                # 1984   , 2888      , 661
DSI = np.empty((L.shape[0], L.shape[1], dLimit))    
altDSI = np.empty((L.shape[0], L.shape[1], dLimit)) 

count = 0
for i in range (0, DSI.shape[0]): 
    for j in range (0, DSI.shape[1]):
        
        for k in range (0, DSI.shape[2]):
            
            altShift = max ((j-k), 0)
            shift = min ((j+k), 287)
            
            
            Red = (L[i][j][0] - R[i][shift][0])**2  
            Green = (L[i][j][1] - R[i][shift][1])**2  
            Blue = (L[i][j][2] - R[i][shift][2])**2
            
            altRed = (R[i][j][0] - L[i][altShift][0])**2  
            altGreen = (R[i][j][1] - L[i][altShift][1])**2  
            altBlue = (R[i][j][2] - L[i][altShift][2])**2
        
            SOS = Red+Green+Blue
            altSOS = altRed+altGreen+altBlue
            DSI[i][j][k] = SOS
            altDSI[i][j][k] = altSOS




# Gaussian and Bilateral filtering

import skimage
import cv2

sig = 2

for k in range (0, DSI.shape[2]):
    
    color = 55
    space = 55
    diam = 9
    
    g = DSI[:,:,k] 
    f = altDSI[:,:,k]
  
    gauss = skimage.filters.gaussian(g, sigma = sig)
    gauss2 = skimage.filters.gaussian(f, sigma = sig)

    DSI[:,:,k] = gauss
    altDSI[:,:,k] = gauss2
    
   

    # NOTE: The below is commented code for turning on bilateral filtering on.
    # To turn on, uncomment this code and comment the above gaussian code 
    # (except color, space, and diam)

    #g = np.float32(DSI[:,:,k])
    #f = np.float32(altDSI[:,:,k])
    
    #bilat = cv2.bilateralFilter(src = g, d = diam, sigmaColor = color , sigmaSpace = space) 
    #bilat2 = cv2.bilateralFilter(src = f, d = diam, sigmaColor = color , sigmaSpace = space) 

    #DSI[:,:,k] = bilat
    #altDSI[:,:,k] = bilat2
   




# Finding minimum disparaties

DSImap = np.empty((L.shape[0], L.shape[1])) 
altDSImap = np.empty((L.shape[0], L.shape[1])) 
                        
minD = 9999

                        
for i in range (0, DSI.shape[0]): 
    for j in range (0, DSI.shape[1]):
            
        minD = 9999
        depth = 0
        
        altminD = 9999
        altdepth = 0
        
        for k in range (0, DSI.shape[2]):
            
            curr = DSI[i][j][k]
             
            if (curr < minD):
                minD = curr
                depth = k
                
        for k in range (0, DSI.shape[2]):
            
            altcurr = altDSI[i][j][k]
             
            if (altcurr < altminD):
                altminD = altcurr
                altdepth = k
                
        DSImap [i][j] = depth
        altDSImap [i][j] = altdepth
                        
pylab.imshow(altDSImap)





#RMS calculations:

truth = np.load('/Users/Hasan/Desktop/gt.npy')
RMS = 0
altRMS = 0

for i in range (0, DSImap.shape[0]): 
    for j in range (0, DSImap.shape[1]):
        RMS += (DSImap[i][j] - truth[i][j])**2
        altRMS += (altDSImap[i][j] - truth[i][j])**2

RMS = (RMS / (DSImap.shape[0]*DSImap.shape[1]))**(0.5)
altRMS = (altRMS / (altDSImap.shape[0]*altDSImap.shape[1]))**(0.5)

print 'RMS value w/d ', diam, ', colorSigma ', color,', colorSpace ', space,', is: ', RMS
print 'altRMS value w/d ', diam, ', colorSigma ', color,', colorSpace ', space,', is: ', altRMS




#Left right check:

print altDSImap.shape
print DSImap.shape

occluded = np.empty((L.shape[0], L.shape[1])) 

for i in range (0, altDSImap.shape[0]): 
    for j in range (0, altDSImap.shape[1]):
                
            if (abs(altDSImap[i][j] - DSImap[i][min(j+altDSImap[i][j], altDSImap.shape[1]-1)]) < 15):
                #print 'i:, ', i, ' j: ', j,', occlusion!'
                occluded[i][j] = DSImap[i][j]  
            else:
                occluded[i][j] = 0 
                

# Part 2: HOMOGRAPHIES----------------------------------------------------------------------------------------------------------------

A = cv2.imread('/Users/Hasan/Desktop/Workspace/Computer_Vision/Project2/rschool.jpg')
B = cv2.imread('/Users/Hasan/Desktop/Workspace/Computer_Vision/Project2/lschool.jpg')

# Calcuating keypoints and descriptors

sift = cv2.xfeatures2d.SIFT_create()

kpA, desA = sift.detectAndCompute(A,None)
kpB, desB = sift.detectAndCompute(B,None)

#print kp1.dtype

bf = cv2.BFMatcher()
matches = bf.knnMatch(desA,desB, k=2)

#print 'matches: ', matches

good = []
for m,n in matches:
    if m.distance < 0.75*n.distance:
        good.append([m])




# Calculating Homographies

def homog(originalC, mappedC):
    
    A = np.empty([8,8])
    y = np.empty([8,1])
    
    for i in range(0, 4):
        (xa,ya) = originalC[i]
        (xb,yb) = mappedC[i]
        
        A[i*2][:] = [-xb, -yb, -1, 0, 0, 0, xa*xb, xa*yb]
        A[(i*2)+1][:] = [0,0,0,-xb,-yb,-1,ya*xb,ya*yb]
        
        y[i*2][0] = -xa
        y[(i*2)+1][0] = -ya
    
    #print 'Matrix A: '
    #print A
    
    params = np.linalg.lstsq(A, y)
    
    H = np.array([  [params[0][0][0], params[0][1][0], params[0][2][0]],
                    [params[0][3][0], params[0][4][0], params[0][5][0]], 
                    [params[0][6][0], params[0][7][0], 1]])
    
    H = np.around(H, decimals=2)
    
    return H






# Applying homographies

def applyHomog (H, x, y):
    
    #print x, y
    xi = np.array([ [x], [y], [1] ])
    
    #print xi
    #print H
    
    #print H.dtype
    #print xi.dtype
    
    sol = np.matmul(np.asarray(H),np.asarray(xi))
    
    #print sol

    return sol[0][0], sol[1][0] 





# RANSAC

import random

hom = 0
tDiff = 0
homographies = np.empty([len(good)-1, 3,3])
inlierArr = np.empty([len(good)-1])
threshold = 40000

for i in range (0, len(good)-1): 
        
        tDiff = 0
        currInliers = 0
        
        selection1 = random.sample(good, 1)
        selection2 = random.sample(good, 1)
        selection3 = random.sample(good, 1)
        selection4 = random.sample(good, 1)
        
        x1, y1 = kpA[selection1[0][0].queryIdx].pt
        x1p, y1p = kpB[selection1[0][0].trainIdx].pt     
        x2, y2 = kpA[selection2[0][0].queryIdx].pt
        x2p, y2p = kpB[selection2[0][0].trainIdx].pt      
        x3, y3 = kpA[selection3[0][0].queryIdx].pt
        x3p, y3p = kpB[selection3[0][0].trainIdx].pt       
        x4, y4 = kpA[selection4[0][0].queryIdx].pt
        x4p, y4p = kpB[selection4[0][0].trainIdx].pt
        
        originalC = [(x1,y1), (x2, y2), (x3, y3), (x4, y4)]
        mappedC = [(x1p,y1p), (x2p, y2p), (x3p, y3p), (x4p, y4p)]
        
        # calculating homogrpahy:
        
        H = homog (originalC, mappedC)
        
        # looping through all other good matches w/ this homography
        
        xDiff = 0 
        yDiff = 0     
        
        
        
        for j in range (0, len(good)-1):
            
            x,y = kpA[good[j][0].queryIdx].pt
            
            Tx,Ty = kpA[good[j][0].trainIdx].pt
            
            xp, yp = applyHomog (H, x, y)
            
            diff = ((Tx - xp)**2 + (Ty - yp)**2)/2
            
            #print 'Homography ', hom, '.Difference value for this match: ', diff
            
            tDiff +=diff
           
            
            if (diff < threshold ): 
                currInliers+=1
                     
        #print 'This homographies total difference value is: ', tDiff
        #print 'Homography', hom, ' has ', currInliers, ' currInliers'   
        
        hom+=1
        
        homographies[i] = H
        inlierArr[i] = currInliers

bestInlierIdx = np.argmax(inlierArr)
bestHom = homographies[bestInlierIdx]

print 'The best homography has ', inlierArr[bestInlierIdx], 'inliers out of ', len(good), 'matches,  with an error threshold of', threshold



# Warping

import skimage, skimage.transform, numpy.linalg

def composite_warped(A, B, bestHom):
    "Warp images a and b to a's coordinate system using the homography H which maps b coordinates to a coordinates."
    out_shape = (A.shape[0], 2*A.shape[1])                               # Output image (height, width)
    p = skimage.transform.ProjectiveTransform(np.linalg.inv(H))       # Inverse of homography (used for inverse warping)
    bwarp = skimage.transform.warp(B, p, output_shape=out_shape)         # Inverse warp b to a coords
    bvalid = np.zeros(B.shape, 'uint8')                               # Establish a region of interior pixels in b
    bvalid[1:-1,1:-1,:] = 255
    bmask = skimage.transform.warp(bvalid, p, output_shape=out_shape)    # Inverse warp interior pixel region to a coords
    apad = np.hstack((skimage.img_as_float(A), np.zeros(A.shape))) # Pad a with black pixels on the right
    return skimage.img_as_ubyte(np.where(bmask==1.0, bwarp, apad))    # Select either bwarp or apad based on mask


done = composite_warped(A, B, bestHom)
done = done[:,:,::-1] 
pylab.imshow(done)
plt.show()
