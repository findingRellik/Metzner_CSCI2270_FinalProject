# Metzner_CSCI2270_FinalProject
Final Project: Universal Grade Calculator

Project Summary
This a Universal Grade Calculator. You can calculate your current or final grade, print your grades, find out your strength and weakness in the class, minimum grade on final to pass the class, and change any grades you just entered thus far...(adding grades coming soon). Nothing high tech here, it's a linked list of arrays in which you manually enter in you class grades to calculate your current grade since D2L doesn't do it for you (WHY??). When entering the number of grades in a section, make sure you only alot enough space in the array for grades you've actually earned, if you've earned 5 grades then alot 5 slots in the array. When it asks for a number only enter a number since it uses cin>>. Always include the final in the count of your finals even if you haven't taken it, the program accounts for it.

How to run: Compile and run the program using code-blocks. A terminal will open with a list of options to choose from. Otherwise compile the files together with a way that works for you.

Dependencies 
The only libraries inluded are iostream and istream(getline). So if your compiler can't handle that, I'm sorry.

 
System Requirements

My program was built and run on Linux (Spring'16 Ubuntunu VM virtualbox).

Group Members 
None 
 
Contributors 
Parker

Open issues/bugs 
Bugs:
If it's asking for a number and you accidentally hit a letter, congrats you broke the program (I used cin>> instead of getline because I hate converting strings).

Adding on:
I didn't have time to create a function to add new grades to a section... but then again what's the point if you can't 'save' your class to the computer which was my plan initially using s11n or write out to a file, then read it in when you want to 'load' a class.
I would like the minimum grade to pass also be minimum grade needed for an A, B, C...etc.
Also some classes drop the lowest score or three in a particular section, I would like to add that capability eventually.
