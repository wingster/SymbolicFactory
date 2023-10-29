CMake in this direcotry is not currently setup to automatically/lazily build the python venv for the relevant dependent python packages
Current issues :
1. There aren't enough datapoints to confirm if the generated test code have correct syntax and semantics. The output will need to be reviewed for accuracy
2. User will need to supply their own GOOGLE_API_KEY outside of the repo

Given that above, the current approach is to generate the test files via LLM as a manual step. Then commit the adjusted output cpp files into the repo

Util.py would look up .env from parent directories to pick up GOOGLE_API_KEY

pip packages required by the python scripts are:
#!pip install google-generativeai
#!pip install python-dotenv