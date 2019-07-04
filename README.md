#Задача3 Спутники  
В космос запущены два спутника, которые передают некоторые сообщения на землю. 
Для передачи используются два сигнала: A и B. Сообщение состоит из последовательности этих сигналов. 
У каждого спутника есть свой позывной - уникальная последовательность сигналов. 
В позывных обоих спутников одинаковое количество сигналов. Никакой спутник не начинает свою передачу, пока ее не закончит другой. 
Передача сообщения с каждого спутника начинается передачей его позывного. Далее следует последовательность сигналов, которая, собственно и составляет сообщение. В сообщении спутника может встретиться последовательность сигналов, совпадающая с его позывным или позывным другого спутника. Тогда в передаче такая последовательность "экранируется" специальным набором сигналов: ABBA - кавычкой в начале последовательности. Сама последовательность ABBA экранируется своим повторением. В позывных набор символов кавычка не встречается. Например:  
   Позывные спутника 1:    
   **AAAA**                
   Позывные спутника 2:  
   **ABAA**                
   Сообщение спутника 1:       **AAAA**BBBABABBA - простое сообщение с текстом BBBABABBA (кавычка на конце допустима???)   
Получая серию передач с обоих спутников, приемник должен определить количество передач, источник каждой передачи и освободить ее от кавычек и позывных.  
Например:  
    **AAAA**B*ABBA***ABAA**BB**ABAA**BAAAAA*ABBA***ABAA**BA      
    Спутнику 1 принадлежит сообщение  
    BABAABB      
    Спутнику 2 принадлежит сообщение   
    BAAAAAABAABA      
Требуется написать программу для приемника, которая по введенной последовательности определяет: общее количество сообщений,
отдельно печатает все сообщения, принятые со спутника 1 и со спутника 2, освобожденные от кавычек и позывных в заголовке сообщения.

Ввод: производится из файла SPACE.DAT. Файл содержит три строки.  
В первой строке - позывные первого спутника, во второй - позывные второго спутника,  
в третьей - строка символов {A,B} длиной не более 255 символов.  
Вывод производить в файл MESS.DAT.  
В первой строке файла должно быть целое число - количество принятых передач, во второй строке надпись - SPUTNIK1, затем идут сообщения, 
принятые от спутника 1 (каждое в отдельной строке), затем надпись SPUTNIK2 и сообщения,   
принятые от спутника 2 (каждое в отдельной строке)  

ABA  
BBB  
ABAAAAAAAABBBAAAABBAABABBBBA  

Вывод:  
3  
SPUTNIK1  
AAAAAAA  
SPUTNIK2  
AAAABA  
BA  
***************************************************************************************************************************************

Task 3 Satellites
Two satellites launched into space transmit some messages to the earth.
Two signals are used for transmission: A and B. Any message consists of a sequence of these signals.
Each satellite has its own call sign - a unique sequence of signals.
The call signs of both satellites have the same number of signals.
No satellite starts its transmission until another one finishes it.
Transmission of a message from each satellite begins with its call sign.
Call sign is followed by the satellite's message.
A satellite message may encounter a sequence of signals that coincides with its call sign or that of another satellite.
Then, in the transmission, such a sequence is “screened” by a special set of signals: ABBA - a "quotation mark" at 
the beginning of the sequence.
The ABBA sequence itself is screened by its repetition. There is no quotation mark in the call sign.
For example:
    Callsign of satellite 1: AAAA
    Callsign of satellite 2: ABAA
    Satellite 1: AAAABBBABABBA message - simple message with text BBBABABBA (quotation mark at the end is valid ???)
Receiving a series of transmissions from both satellites, the receiver must determine the number of transmissions,
the source of each transmission and filter out "quotes" and call signs.
For example:
    AAAABABBAABAABBABAABAAAAAABBAABAABA
    Satellite 1 owns the message BABAABB
    Satellite 2 owns the message BAAAAAABAABA
It is required to write a program for the receiver, which according to the entered sequence determines:
the total number of messages, separately prints all messages received from satellite 1 and from satellite 2,
freed from quotes and call signs in the message header.

Input: made from the SPACE.DAT file. The file contains three lines.
In the first line - call signs of the first satellite, in the second - call signs of the second satellite,
in the third, the string of characters {A, B} which is no longer than 255 characters.
Output is produced into file MESS.DAT.
The first line of the file should contain an integer - the number of received broadcasts,
the second line contains the label - SPUTNIK1, then the messages go,
received from satellite 1 (each on a separate line), 
then the label SPUTNIK2 and messages,
received from satellite 2 (each on a separate line)

ABA
BBB
ABAAAAAAAABBBAAAABBAABABBBBA

OUTPUT - MESS.DAT:
3
SPUTNIK1
AAAAAAA
SPUTNIK2
AAAABA
BA
 



 
