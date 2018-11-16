import sys
import os
import re


def main():
    # Check input for the program.
    checker = ArgsChecker()
    if not checker.checkInputArgsAreCorrect():
        return 1

    if checker.processMode == checker.PROCESS_FROM_DIR:
        dirProcesser = FromDirProcesser()
        dirProcesser.process(checker.csvFilePath)

    if checker.processMode == checker.PROCESS_CERTAIN_FILE:
        certainFileProcesser = FromCertainFileProcesser(
            checker.csvFilePath, checker.resultNFilePath, checker.lsNFilePath
        )
        certainFileProcesser.process(checker.varNum)

    # End of the program.
    print('End of the program.')
    return 0


class ArgsChecker:
    PROCESS_CERTAIN_FILE = 1
    PROCESS_FROM_DIR = 2

    def __init__(self):
        self.varNum = 0
        self.processMode = 0

    def checkInputArgsAreCorrect(self):
        return self._checkArgv() and self._checkFilesExist() and self._checkFilesNamingFormat()

    def _checkArgv(self):
        # Check command line arguments for amount of input files.
        argv = sys.argv[1:]
        if len(argv) != 3 and len(argv) != 1:
            print('Usage: python app.py [group(.csv)] ([resultN(.txt)] [lsN(.txt)])')
            return False
        # Save mode of processing.
        if len(argv) == 3:
            self.processMode = self.PROCESS_CERTAIN_FILE
        elif len(argv) == 1:
            self.processMode = self.PROCESS_FROM_DIR
        return True

    def _checkFilesExist(self):
        # Check if files from sys.argv really exist.
        for arg in sys.argv[1:]:
            fullFileName = os.path.splitext(arg)
            # This program works with files without extensions.
            if not os.path.exists(arg) and not os.path.exists(fullFileName[0]):
                print('File %s does not exist.' % arg)
                return False
        return True

    def _checkFilesNamingFormat(self):
        # Pass if FROM_DIR mode.
        if self.processMode == self.PROCESS_FROM_DIR:
            # Save .csv filepath.
            self.csvFilePath = sys.argv[1]
            return True

        # Check if files from sys.argv have a proper naming format.
        fileNames = sys.argv[1:]

        # Check [.csv] file.
        # It has a format [XX.csv] or [XX], where X is a digit.
        # Example: [51.csv] or [51].
        csvMatch = re.match(r'^(\d){2}(\.csv)?$', fileNames[0], re.I)
        if not csvMatch:
            print('Your [XX.csv] file has incorrect name.')
            print('Please use [NN.csv] or [NN] format, where N is a digit.')
            return False

        # Check file [resultNVar.txt].
        # It has a format [resultNVar.txt] or [resultNVar], where NVar is one or two digits.
        # Example: [result5.txt], or [result15].
        resultNFileMatch = re.match(r'^result(\d){1,2}(\.txt)?$', fileNames[1], re.I)
        if not resultNFileMatch:
            print('Your [resultN.txt] file has incorrect name.')
            print('Please use [resultN.txt] or [resultN] format, where N is a 1- or 2- digit variant number.')
            return False

        # Check file [lsN.txt].
        # It has a format [lsN.txt] or [lsN], where N is 1- or 2- digit variant number.
        # Example: [ls5.txt] or [ls15].
        lsNFileMatch = re.match(r'^ls(\d){1,2}(\.txt)?$', fileNames[2], re.I)
        if not lsNFileMatch:
            print('Your [lsN.txt] file has incorrect name.')
            print('Please use [lsN.txt] or [lsN] format, where N is 1- or 2- digit variant number.')
            return False

        # Check if files [lsN.txt] and [resultNVar.txt] have the same variant number.
        firstNum = re.match(r'^result((\d){1,2})(\.txt)?$', fileNames[1], re.I).group(1)
        secondNum = re.match(r'^ls((\d){1,2})(\.txt)$', fileNames[2], re.I).group(1)
        if firstNum != secondNum:
            print('Files [resultN.txt] and [lsN.txt] are not for the same variant.')
            return False

        # Save the variant number.
        self.varNum = int(firstNum)
        # Save .csv filepath.
        self.csvFilePath = fileNames[0]
        # Save resultN.txt filepath.
        self.resultNFilePath = fileNames[1]
        # Save lsN.txt filepath.
        self.lsNFilePath = fileNames[2]

        return True


class FromDirProcesser:

    def process(self, csvFilePath):
        if not self._processCsvFile(csvFilePath):
            print('Error occured while reading %s file' % csvFilePath)
            return False

        # Go through all lines and check each variant.
        for variant in self.csvFileContent:
            varMatch = re.match(r'^(\d){1,2}$', variant, re.I)
            varMatchErr = re.match(r'^((\d){1,2}),Err$', variant, re.I)
            varMatchSemiColon = re.match(r'^((\d){1,2}),$', variant, re.I)
            # If line is not filled with results:
            if varMatch or varMatchErr or varMatchSemiColon:
                if varMatch:
                    curVar = int(varMatch.group())
                elif varMatchErr:
                    curVar = int(varMatchErr.group(1))
                elif varMatchSemiColon:
                    curVar = int(varMatchSemiColon.group(1))

                print("%r" % curVar)

                self.CertainValProcessor = FromCertainFileProcesser(
                    csvFilePath,
                    str.format("result%i.txt" % curVar),
                    str.format("ls%i.txt" % curVar)
                )
                self.CertainValProcessor.process(curVar)


    def _processCsvFile(self, csvFilePath):
        # Read content from .csv file.
        self.csvFileContent = []
        try:
            f = open(csvFilePath, "r", encoding="utf-8-sig")
            self.csvFileContent = [line.rstrip('\n') for line in f]
        except:
            print('Error occured while reading file %s.' % csvFilePath)
            return False
        return True


class FromCertainFileProcesser:

    def __init__(self, csvFilePath, resultNFilePath, lsNFilePath):
        self.resultNFilePath = resultNFilePath
        self.lsNFilePath = lsNFilePath
        self.csvFilePath = csvFilePath

    def process(self, varNum):
        self._processResultNFile(varNum)
        self._writeResult(self.csvFilePath, varNum)

    def _processResultNFile(self, varNum):
        resultNContent = []
        self._marks = []

        # Read content from lsN.txt file.
        if not self._processLsNFile():
            print('Error occured while reading file %s.' % self.lsNFilePath)
            self._marks.append('Err')
            return False

        # Read content from resultN.txt file.
        try:
            f = open(self.resultNFilePath, "r", encoding="utf-8-sig")
            resultNContent = [line.rstrip('\n') for line in f if line.rstrip('\n')]
        except:
            print('Error occured while reading file %s.' % self.resultNFilePath)
            self._marks.append('Err')
            return False

        # Save username.
        self.userName = resultNContent[0]
        # Check variant.
        if varNum != int(resultNContent[1]):
            print('Error: variant missmatch. In file:', int(resultNContent[1]))
            self._marks.append('Err')
            return False

        # Testing.
        print('Checking @%s var%i' % (self.userName, varNum))

        # "labs" task.
        if resultNContent[2] == str.format("lab%i" % varNum) \
                and resultNContent[3] == str.format("lab%i" % (varNum + 1)):
            self._marks.append('1')
        else:
            self._marks.append('labs-')
        # Testing:
        print('labs', self._marks[0])

        # "hard1" task.
        try:
            first1, *middle1, last1 = resultNContent[4].split()
            first2, *middle2, last2 = resultNContent[5].split()
        except:
            print('Error in "hard1" task: incorrect data format.')
            self._marks.append('Err')
            return False

        if resultNContent[4] and resultNContent[5] \
                and first1 == first2 \
                and str.format("tree%i_h" % varNum) == last1 \
                and str.format(".tree%i" % varNum) == last2:
            self._marks.append('1')
        else:
            self._marks.append('hard1-')
        # Testing
        print('hard1', self._marks[1])

        # "mount" task.
        startingLine = 6
        endingLine = startingLine
        for i, line in enumerate(resultNContent[startingLine:]):
            if '-rw' in line:
                endingLine = startingLine + i
                break

        strToFind = str.format('/home/%s/mount/NTFS' % self.userName)
        strToFind2 = str.format('/home/%s/mount/EXT4' % self.userName)
        firstStrFound = False
        secondStrFound = False
        for line in resultNContent[startingLine:endingLine]:
            if strToFind in line:
                firstStrFound = True
            if strToFind2 in line:
                secondStrFound = True
        if firstStrFound and secondStrFound:
            self._marks.append('1')
        else:
            self._marks.append('mount-')
        # Testing
        print('mount', self._marks[2])

        # "hard2" task.
        try:
            first1, *middle1, last1 = resultNContent[endingLine].split()
            first2, *middle2, last2 = resultNContent[endingLine + 1].split()
        except:
            print('Error in "hard2" task: incorrect data format.')
            self._marks.append('Err')
            return False

        if resultNContent[endingLine] and resultNContent[endingLine + 1] \
                and first1 != first2 \
                and str.format("tree%i_h" % varNum) == last1 \
                and str.format(".tree%i" % varNum) == last2 \
                and self._argsInText([first1, last1], self.lsNContent) \
                and self._argsInText([first2, last2], self.lsNContent):
            self._marks.append('1')
        else:
            self._marks.append('hard2-')
        # Testing
        print('hard2', self._marks[3])

        # "diff" task.
        if self.userName in resultNContent[endingLine + 3] \
                and str.format('lab%i' % varNum) in resultNContent[endingLine + 6] \
                and str.format('lab%i' % (varNum + 1)) in resultNContent[endingLine + 7] \
                and str.format('lect%i' % (varNum - 1)) in resultNContent[endingLine + 9] \
                and str.format('lect%i' % varNum) in resultNContent[endingLine + 10] \
                and str.format('result%i' % varNum) in resultNContent[endingLine + 13] \
                and '3 directories, 7 files' in resultNContent[endingLine + 16]:
            self._marks.append('1')
        else:
            self._marks.append('diff-')
        # Testing
        print('diff', self._marks[4])

        return True

    def _processLsNFile(self):
        # Read content from lsN.txt file.
        try:
            f = open(self.lsNFilePath, "r", encoding="utf-8-sig")
            self.lsNContent = [line.rstrip('\n') for line in f if line.rstrip('\n')]
        except:
            return False
        return True

    def _argsInText(self, argsLst, textAsLst):
        # Means that all items from argsLst should be in one line.
        for line in textAsLst:
            # I am sorry.
            splittedLine = line.split()
            if (argsLst[0] in splittedLine) and (argsLst[1] in splittedLine):
                return True
        return False

    def _writeResult(self, csvFilePath, varNum):
        # Write result to .csv file.
        # Note, that result will be on certain line in .csv file.
        csvFileContent = []
        try:
            f = open(csvFilePath, "r", encoding="utf-8-sig")
            csvFileContent = [line.rstrip('\n') for line in f]
        except:
            print('Error occured while reading file %s.' % csvFilePath)
            return False

        # Format data to write to .csv file.
        toWrite = self._marks
        toWrite.insert(0, str(varNum))
        if 'Err' not in self._marks:
            toWrite.append(str(self._getMarksSum()))
        csvFileContent[int(varNum) - 1] = ','.join(toWrite)
        csvFileContentWithNewLines = [(line+'\n') for line in csvFileContent]

        # Write data to .csv file.
        try:
            f = open(csvFilePath, "w", encoding="utf-8-sig")
            f.writelines(csvFileContentWithNewLines)
        except:
            print('Error occured while writing data to file %s.' % csvFilePath)
            return False

        return True

    def _getMarksSum(self):
        toRet = 0
        for mark in self._marks:
            if mark == '1':
                toRet += 1
        return toRet


if __name__ == '__main__':
    main()
