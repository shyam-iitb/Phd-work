#!/bin/bash
rm DPA*
rm NIEL*
rm DOSE*
echo "The Script is working..."
ls damageSi0**_fort*24 > DPA.txt
ls damageSi0**_fort*25 > NIEL.txt
ls damageSi0**_fort*26 > DOSE.txt
filename1="DPA.txt"
filename2="NIEL.txt"
filename3="DOSE.txt"
righe1=$(wc -l $filename1 | awk '{print $1}')
righe2=$(wc -l $filename2 | awk '{print $1}')
righe3=$(wc -l $filename3 | awk '{print $1}')
echo $righe1
echo $righe2
echo $righe3
echo Value of count is RigE1:$righe1
echo Value of count is RigE2:$righe2
echo Value of count is RigE3:$righe3
# while loop for DPA
riga=0
while [ $riga -lt $righe1 ]; do
let riga=riga+1
echo Value of count is:$riga
current=$(head -$riga $filename1 | tail -1)
echo $current

#singolofile=$current

#righe_s=$(wc -l $singolofile | awk '{print $1}')

cat $current | awk 'NR>17' >> DPA1.txt

done
# while loop for NIEL
riga=0
while [ $riga -lt $righe2 ]; do
let riga=riga+1
echo Value of count is:$riga
current=$(head -$riga $filename2 | tail -1)
echo $current

#singolofile=$current

#righe_s=$(wc -l $singolofile | awk '{print $1}')

cat $current | awk 'NR>17' >> NIEL1.txt

done
#while loop for DOSE
riga=0
while [ $riga -lt $righe3 ]; do
let riga=riga+1
echo Value of count is:$riga
current=$(head -$riga $filename3 | tail -1)
echo $current

#singolofile=$current

#righe_s=$(wc -l $singolofile | awk '{print $1}')

cat $current | awk 'NR>17' >> DOSE1.txt

done
sed -e 's/.*1.0000E+00//g' DPA1.txt > DPA2.txt
sed -e 's/Number of hit cells: *[01]//g' DPA2.txt > DPA3.txt 
sed -e 's/.*1.0000E+00//g' NIEL1.txt > NIEL2.txt
sed -e 's/Number of hit cells: *[01]//g' NIEL2.txt > NIEL3.txt 
sed -e 's/.*1.0000E+00//g' DOSE1.txt > DOSE2.txt
sed -e 's/Number of hit cells: *[01]//g' DOSE2.txt > DOSE3.txt 
#sed -e 's/0.0000E+00//g' Lista3.txt > Lista4.txt

#sed -e 's/o//g' Lista4.txt > Lista5.txt
#root -l Plotdamage.C


sed -e 's/[ 1] //g' DPA3.txt  > DPA4.txt
sed -e '/^$/d' DPA4.txt  > DPA5.txt
sed -e 's/[ 1] //g' NIEL3.txt  > NIEL4.txt
sed -e '/^$/d' NIEL4.txt  > NIEL5.txt
sed -e 's/[ 1] //g' DOSE3.txt  > DOSE4.txt
sed -e '/^$/d' DOSE4.txt  > DOSE5.txt
#sed -e 's/[eE]+*/*10^/g' Lista6.txt > Lista7.txt

echo "account the lines of the file"
rig1=$(wc -l DPA5.txt | awk '{print $1}')
echo "The number of Events in DPA are:" $rig1

rig2=$(wc -l DPA1.txt | awk '{print $1}')
echo "The number of primary in DPA are:" $((rig2/4))

rig3=$(wc -l NIEL5.txt | awk '{print $1}')
echo "The number of Events in NIEL are:" $rig5

rig4=$(wc -l NIEL1.txt | awk '{print $1}')
echo "The number of primary in NIEL are:" $((rig6/4))
rig5=$(wc -l DOSE5.txt | awk '{print $1}')
echo "The number of Events in DOSE are:" $rig5

rig6=$(wc -l DOSE1.txt | awk '{print $1}')
echo "The number of primary in DOSE are:" $((rig6/4))
#root -l isto.c
