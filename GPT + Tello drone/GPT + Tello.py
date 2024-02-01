import openai
import re
import argparse
import math
import numpy as np
import os
import json
import time
from djitellopy import Tello

# Initialize argument parser
parser = argparse.ArgumentParser()
parser.add_argument("--prompt", type=str, default="prompts/tello_instructions.txt")
parser.add_argument("--sysprompt", type=str, default="prompts/tello_sys_instructions.txt")
args = parser.parse_args()

# Load configuration
with open("config.json", "r") as f:
    config = json.load(f)

print("Initializing ChatGPT...")
openai.api_key = config["OPENAI_API_KEY"]

# Read system prompt
with open(args.sysprompt, "r") as f:
    sysprompt = f.read()

chat_history = [
    {
        "role": "system",
        "content": sysprompt
    },
    {
        "role": "assistant",
        "content": sysprompt
    }
]

# Function to interact with ChatGPT
def ask(prompt):
    chat_history.append(
        {
            "role": "user",
            "content": prompt,
        }
    )
    completion = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=chat_history,
        temperature=0
    )
    chat_history.append(
        {
            "role": "assistant",
            "content": completion.choices[0].message.content,
        }
    )
    return chat_history[-1]["content"]

print(f"Done.")

# Regex for extracting Python code
code_block_regex = re.compile(r"```(.*?)```", re.DOTALL)

# Function to extract Python code
def extract_python_code(content):
    code_blocks = code_block_regex.findall(content)
    if code_blocks:
        full_code = "\n".join(code_blocks)
        if full_code.startswith("python"):
            full_code = full_code[7:]
        return full_code
    else:
        return None

# Color class for terminal output
class colors:
    RED = "\033[31m"
    ENDC = "\033[m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"

# Initialize Tello Drone
print(f"Initializing Tello Drone...")
tello = Tello()
tello.connect()
print(f"Done.")

# Read user prompt
with open(args.prompt, "r") as f:
    prompt = f.read()

# Interact with ChatGPT
ask(prompt)
print("Welcome to the Tello drone chatbot! I am ready to help you with your Tello drone questions and commands.")

while True:
    question = input(colors.YELLOW + "Tello> " + colors.ENDC)

    if question == "!quit" or question == "!exit":
        break

    if question == "!clear":
        os.system("cls" if os.name == 'nt' else 'clear')
        continue

    response = ask(question)
    print(f"\n{response}\n")

    code = extract_python_code(response)
    if code is not None:
        print("Please wait while I run the code for Tello...")
        try:
            exec(code)
            print("Done!\n")
        except Exception as e:
            print(f"Error executing the code: {e}")
