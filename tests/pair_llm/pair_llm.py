import os
from utils import get_api_key
import google.generativeai as palm
from google.api_core import retry, client_options as client_options_lib

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

import pprint
for model in palm.list_models():
    pprint.pprint(model) # 🦎🦦🦬🦄


CODE_BLOCK = """ 
# replace this with your own code
def foo(a):
  b = a + 1
  return 2*b
"""

prompt_template = """
Can you please explain how this code works?

{question}

Use a lot of detail and make it as clear as possible.
"""

completion = generate_text(
    prompt = prompt_template.format(question=CODE_BLOCK)
)
print(completion.result)


prompt_template = """
Please write technical documentation for this code and \n
make it easy for a non swift developer to understand:

{question}

Output the results in markdown
"""

completion = generate_text(
    prompt = prompt_template.format(question=CODE_BLOCK)
)
print(completion.result)