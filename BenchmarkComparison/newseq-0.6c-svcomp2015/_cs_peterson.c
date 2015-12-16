
Error while performing duplicator->labeler:

Traceback (most recent call last):
  File "./new.py", line 197, in main
    m.loadfromstring(sourcecode, cseqenvironment)
  File "/home/chinmay/Documents/Tools/newseq-0.6c-svcomp2015/labeler.py", line 88, in loadfromstring
    self.output += self.__createMain(rounds)
  File "/home/chinmay/Documents/Tools/newseq-0.6c-svcomp2015/labeler.py", line 549, in __createMain
    threadsize = self.__lines[self.__threadName[t]]
KeyError: 'main'


 parsing coords: <>
