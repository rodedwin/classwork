This repo is for ECE 531, Summer 2020 at the University of New Mexico
As of 07/16/2020 requestor.c meets the requirements for week 3's 
"Network Communication on ARM" assignment. See below for 
details of the assignment.

For this assignment, you'll need to write a program that uses libcurl to communicate via HTTP. I'd like the program to take some command line arguments, and execute HTTP GET, POST, PUT, and DELETE. the program needs to support the following command line options:

-u/--url
-o/--post
-g/--get
-p/--put
-d/--delete
-h/--help

The final argument will be an arbitrary string. Be careful with your string processing! You'll need to handle oddly formatted strings with unusual characters. The -u/--url flag will need to handle a properly formatted URL (including localhost) followed by a port number. You should be able to have the command line options in any order.

Your program should return any content returned from the request preceded by the HTTP code (404, 200, etc.).

So, if your program, when compiled, is named 'hw', these are some examples of valid invocations:

hw --post --url http://localhost:8080 here is the message I'm posting to the URL!
hw --get --url http://www.cnn.com
hw --put --url http://localhost:8080 put this stuff at the URL
hw --delete --url http://localhost:8080 7839

If I don't submit a string for a verb that requires one, you need to set the exit status according to UNIX standards (e.g. return 0 if everything is OK, some other value otherwise). I'll be running this program on the ARM emulator we configured, so make sure you test it there.
The program needs to work, first and foremost. I will grade via the following guidelines:

100%: Everything works, the program is resistant to crashing on bad input, you've implemented help (via -h/--help) and the HTTP verbs are implemented correctly.
80% You have implemented three verbs.
60%: You have implemented two verbs.
40%: You have implemented one verb.
0%: No verbs implemented.

Implementing help is worth 5%, and implementing short commands (e.g. -o) is worth 5%. Submit the program source code, as a single file attachment, using learn. Include the compilation command (e.g. cc -o hw my_source_code.c) in the first line in the source file as a comment.


