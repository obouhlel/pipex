#Color

Red='\033[0;31m'
Green='\033[0;32m'
Yellow='\033[0;33m'
Cyan='\033[0;36m'
Purple='\033[0;35m'
Color_Off='\033[0m'

#Test
rm -r outfile
echo ${Cyan}
valgrind ./pipex infile "ls -l" "wc -l" outfile
echo ${Green}"INFILE"
cat infile
echo ${Red}"OUTFILE"
cat outfile