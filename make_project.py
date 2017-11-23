#
#   PROJECT GENERATOR TOOL
#

SUPPORTED = {
    "FAMILIES" : {
        "F1": [],
        "F4": []
    }
}

def Usage():
    print("Usage:\n"
          "\tpython make_project.py -n <your_project_name> -m <Full MCU name>\n")

def Build():
    pass

if __name__ == "__main__":
    Build()
else:
    Usage()