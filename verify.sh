# test case verify
#
# requirements
## - ./a.out (実行ファイル)
## - N := [0-9]*
## - ./in/in{N}.txt
## - ./out/out{N}.txt
##   - e.g. (in/in01.txt, out/out01.txt)

printf '\033[34m%s\033[m' '[INFO] '
echo 'start verifying'

inFilePathList=`find . -name in*.txt`

for inFilePath in $inFilePathList
do
  outFilePath=`echo $inFilePath | sed -e "s/in/out/g"`

  # 結果と正答の2ファイル間のdiffを見る
  ./a.out < $inFilePath > temp.txt && diff --unified --color temp.txt $outFilePath && rm temp.txt

  if [ $? -ne 0 ]; then
    printf '\033[31m%s\033[m' '[WA] '
    echo "$inFilePath case result is different from $outFilePath"
    exit 1
  fi

  printf '\033[32m%s\033[m' '[AC] '
  echo "$inFilePath and $outFilePath are verified"
done

printf '\033[34m%s\033[m' '[INFO] '
echo 'verified all test cases'
exit 0
