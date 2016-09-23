#!/bin/bash
rm Lista*
echo "The Script is working..."
ls lyso0**_fort*23 > Lista.txt
filename="Lista.txt"
righe=$(wc -l $filename | awk '{print $1}')
echo $righe
echo Value of count is RigE:$righe
riga=0
while [ $riga -lt $righe ]; do
let riga=riga+1
echo Value of count is:$riga
current=$(head -$riga $filename | tail -1)
echo $current

#singolofile=$current

#righe_s=$(wc -l $singolofile | awk '{print $1}')

cat $current | awk 'NR>17' >> Lista2.txt

done
sed -e 's/.*1.0000E+00//g' Lista2.txt > Lista3.txt
sed -e 's/Number of hit cells: *[01]//g' Lista3.txt > Lista4.txt 

#sed -e 's/0.0000E+00//g' Lista3.txt > Lista4.txt

#sed -e 's/o//g' Lista4.txt > Lista5.txt


sed -e 's/[ 1] //g' Lista4.txt  > Lista5.txt
sed -e '/^$/d' Lista5.txt  > Lista6.txt
#sed -e 's/[eE]+*/*10^/g' Lista6.txt > Lista7.txt

echo "account the lines of the file"
rig=$(wc -l Lista6.txt | awk '{print $1}')
echo "Events are:" $rig

rig2=$(wc -l Lista2.txt | awk '{print $1}')
echo "The primary are:" $((rig2/4))
root -l isto.c
