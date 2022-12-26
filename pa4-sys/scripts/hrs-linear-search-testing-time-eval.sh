# Remove the previous results file

rm -f hrs-linear-search-testing-time-eval.txt

# Run the evaluation

for i in {6000,7000,8000,9000,10000}; do
  ./hrs-linear-search-eval 60000 10000 | tee -a hrs-linear-search-testing-time-eval.txt;
done