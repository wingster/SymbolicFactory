import os
import sys
from utils import get_api_key
import google.generativeai as palm
from google.api_core import retry, client_options as client_options_lib

def read_file(input_file_name):
# Open the input file and read it into a string variable
    try:
        with open(input_file_name, "r") as f:
            file_contents = f.read()
    except FileNotFoundError:
        print("Error: could not find input file {}".format(input_file_name))
        sys.exit(1)
    # Print the contents of the input file
    return file_contents


# Check if the user provided an input file name
if len(sys.argv) < 4:
    print("Usage: python ", sys.argv[0],  " <prompt_file> <input_file_name> <output_file_name")
    sys.exit(1)

# Get the input file name from the command line arguments
prompt_file_name = sys.argv[1]
input_file_name = sys.argv[2]
output_file_name = sys.argv[3]

prompt_template = read_file(prompt_file_name)
input_code = read_file(input_file_name)

api_key = get_api_key()
client_options=client_options_lib.ClientOptions(
        api_endpoint = os.getenv("GOOGLE_API_BASE")
    )
print(api_key)
print(client_options)
palm.configure(
    api_key = get_api_key(),
    transport = "rest",
    client_options = client_options
)

models = [m for m in palm.list_models() if 'generateText' in m.supported_generation_methods]
model_bison = models[0]
model_bison

@retry.Retry()
def generate_text(prompt, 
                  model=model_bison, 
                  temperature=0.0):
    return palm.generate_text(prompt=prompt,
                              model=model,
                              temperature=temperature)


response = palm.generate_text(prompt="The opposite of hot is")
print(response.result) #  'cold.'

print (prompt_template)

completion = generate_text(
    prompt = prompt_template.format(code=input_code)
)
print(completion.result)

# Open the output file for writing.
with open(output_file_name, 'w') as output_file:
    # Write the Python string to the output file.
    output_file.write(completion.result)