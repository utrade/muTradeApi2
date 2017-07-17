import numpy as np

from os import listdir
from os.path import isfile, join

def processFile(inputFile):
    #inputFile = raw_input("Enter input file:")
    a = np.array([])
    iFile = open(inputFile, "r")
    x=iFile.readline().split(",")
    maxCount = 50000
    count=0
    for i in x:
      count +=1
      if count >maxCount:
        break
      if i.isdigit():
        a= np.append(a,int(i))

    outputFile = inputFile +"_Conclusion";
    oFile = open(outputFile, "w")
    oFile.write("Count:"+ str(np.size(a)) + "\n")
    oFile.write("Median:" + str(np.median(a)) + "\n")
    oFile.write("Percentiles:\n")

    oFile.write("50 Percentile:" + str(np.percentile(a, 50)) + "\n")
    oFile.write("90 Percentile:" + str(np.percentile(a, 90)) + "\n")
    oFile.write("95 Percentile:" + str(np.percentile(a, 95)) + "\n")
    oFile.write("99 Percentile:" + str(np.percentile(a, 99)) + "\n")
    oFile.write("99.9 Percentile:" + str(np.percentile(a, 99.9)) + "\n")
    oFile.write("99.99 Percentile:" + str(np.percentile(a, 99.99)) + "\n")
    for i in range(100):
      oFile.write(str(i)+ " Percentile:" + str(np.percentile(a, i)) + "\n")
    oFile.close()

def displayConclusions(fileName):
  iFile = open(fileName,"r")
  x =  fileName.replace("LatencyNumbers_","").replace("_Conclusion","") + "== Count: " + str(int(iFile.readline().strip().split(":")[1])) +  " Median: " + str(float(iFile.readline().strip().split(":")[1])/1000)
  print x
  return x


mypath = "."
files =  [ f for f in listdir(mypath) if isfile(join(mypath,f)) ]
fileList = []
for i in files:
  if "LatencyNumbers_" in i and not "_Conclusion" in i :
    fileList.append(i)

for i in fileList:
  processFile(i)

files =  [ f for f in listdir(mypath) if isfile(join(mypath,f)) ]
fileList = []
for i in files:
  if "_Conclusion" in i :
    fileList.append(i)

latencyNumbers = {}
outFile = open("LatencyNumbers", "w");
internals = []
for i in fileList:
  if "Internal" in i:
    internals.append(i)
others = []
for i in fileList:
  if not "Internal" in i:
    others.append(i)
print "Internals\n=============================================\n"
for i in internals:
  x = displayConclusions(i)
  outFile.write(x+ "\n")

print "Others\n=============================================\n"
for i in others:
  x = displayConclusions(i)
  outFile.write(x+ "\n")





