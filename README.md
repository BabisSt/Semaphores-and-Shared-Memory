# Semaphores and Shared Memory

  The main program starts and creates a main part shared_memory in which it also does attach (attach the other programs in the same part shared memory). Then it makes 4 sets of 2 semaphores (8 in total), where he initializes them to 0.
  Then the rest of the processes are made, in each of them we assign an id starting from 0 to 4. We exec the corresponding programs. The sem_child file has the code of P1 and P2 respectively. Flag 1 is P1 and is our first exec with id = 0. He is responsible for writing and reading things until he is given the TERM message where he terminates the processes. The second exec is done in the enc program. This program contains the enc1 and enc2 code respectively. With id = 1 we correspond to enc1 and with id = 3 to enc2. Their function is to encode the message via an md5 function as well as to break it to see if it has been sent correctly. The third exec is done in the chan program where the chanel with id = 2 is.
Depending on the probability given by the user the message "spoils" by adding x in random places. The next exec is done in enc2 as we said above. Finally with id = 4 we run P2 which will read.
  The programs can go and bring messages from left to right and vice versa until the TERM termination message is given on P1 where the program will end. In order to transfer the messages, the semaphores were used where they "sleep" and "wake up" to convey the messages. <br/> <br/> <br/>






ΕΡΓΑΣΙΑ 1Η ΛΕΙΤΟΥΡΓΙΚΑ ΣΥΣΤΗΜΑΤΑ 2020
Στεβής Χαράλαμπος-Αντώνιος ΑΜ: 1115201600278

Περιεχόμενος εργασίας:
Ένας φάκελος code που περιέχει:
    Makefile
    chan.c
    enc.c
    main.c
    read_write.c
    sem_child.c
    shared_memory.c
    enc.h
    read_write.h
    shared_memory.h

README

Πως τρέχουμε το πρόγραμμα:
    Μέσω του Makefile κάνουμε make all και δημιουργούνται τα exec και τα .o των αρχείων.

    Σε ένα terminal τρέχουμε ./exe 1 (την πιθανότητα που θέλουμε σε δεκαδικο 0 εως 1 πχ:) 0.5
    Το πρόγραμμα exe ξεκινάει και περιμένει να γράψει κάποιος.Επίσης εκτυπώνει το id του shared memory που έχει κάνει attach. Το δεύτερο όρισμα (δηλαδή το 1 σημαίνει ότι αυτό το πρόγραμμα θα γράψει πρώτο. Δηλαδή είναι το P1.
    

    Σε άλλο terminal τρέχουμε ./sem_child (id που έχει εκτυπώσει το exe) 0 4
Το πρώτο όρισμα (δηλαδή το id) είναι το id στο ο οποίο θα κάνει attach το παιδί αυτο. Το δεύτερο όρισμα (δηλαδή το 0) σημαίνει ότι αυτή η διεργασία θα γράψει δεύτερη, δηλαδή ότι είναι ο P2. Το τρίτο όρισμα (δηλαδή το 4) δηλώνει το id της συγκεκριμένης διεργασίας (θα εξηγηθεί παρακάτω).

Τι κάνει το πρόγραμμα:

    Το main πρόγραμμα ξεκινάει και φτιάχνει ένα κύριο κομμάτι shared_memory στο οποίο κανει και attach(attach κάνουμε και τα υπόλοιπα προγράμματα στο ίδιο κομμάτι shared memory). Ύστερα φτιάχνει 4 σετ των 2 σημαφόρων (συνολικά 8), όπου τους αρχικοποιεί σε 0. Ύστερα φτιάχνονται οι υπόλοιπος διεργασίες, σε κάθε μια από αυτές αντιστοιχίζουμε ένα id ξεκινόντας από το 0 έως το 4. Κάνουμε exec τα αντίστοιχα προγράμματα. Στο αρχείο sem_child είναι ο κώδικας των P1 και P2 αντίστοιχα. Με flag 1 είναι ο P1 όπου είναι και το πρώτο μας exec με id =0. Αυτός είναι υπέθυνος για να γράφει και να διαβάζει πράγματα μέχρι να του δωθεί το μήνυμα TERM όπου τερματίζει τις διεργασίες. Το δεύτερο exec γίνεται στο πρόγραμμα enc. Το πρόγραμμα αυτό περιέχει τον κώδικα των enc1 και enc2 αντίστοιχα. Με id=1 αντιστοιχούμε το enc1 και με id=3 το enc2. Λειτουργία τους είναι να κωδικοποιούν το μήνυμα μέσω μιας md5 συνάρτησης καθώς και να το σπάνε για να δουν αν έχει σταλθεί σωστα. Το τρίτο exec γίνεται στο πρόγραμμα chan όπου είναι το chanel με id=2 . Σε αυτό το πρόγραμμα ανάλογα με την πιθανότητα που έχει δωθεί απο τον χρήστη το μήνυμα "χαλάει" προσθένοντας x σε τυχαίες θέσεις. Το επόμενο exec έχει γίνει στο enc2 όπως είπαμε παραπάνω. Τέλος με id=4 τρέχουμε εμείς το P2 το οποίο θα διαβάζει.
    Το πρόγραμματα μπορεί να πηγαίνει και να φέρνει μηνύματα από αριστερά προς δεξιά και το ανάποδο μέχρι να δωθεί το μήνυμα τερματισμού TERM στον P1 όπου το πρόγραμμα θα τερματίσει. ΓΙα να γίνει η μεταφορά των μηνυμάτων χρησιμοποιήθηκαν οι σημαφόρει όπου σε ζεύγει "κοιμούνται" και "ξυπνούν" για να μεταφέρουν τα μηνύματα.
Ο τρόπος με τον οποίο λειτουργούν οι σημαφόρει είναι ότι όλοι αρχικά περιμένον. Ύστερα ξυπνάνε από τον προηγούμενο τους (αριστερά ή δεξιά τους διεργασία ανάλογα με την φορά του μηνύματος) και αφού εκτελέσουν την δουλεία τους οι ίδιοι κοιμούνται και ξυπνάνε τον επόμενό τους.

Τι δεν μπορεί να κάνει το πρόγραμμα: 
   
    Σε περίπτωση αλλαγής του μηνύματος το πρόγραμμα δεν το διορθώνει και το μήνυμα λαμβάνεται λάθος. To πρόγραμμα δεν τερματίζει από το πρώτο μήνυμα. Το πρόγραμμα δεν διαγράφει το κομμάτι της shared_memory.
