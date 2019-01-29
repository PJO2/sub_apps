# gabuzo.py
# a simple shadok -> int conversion using python
# -----------------------------------------------
import sys
CVT = { "GA": "0", "BU": "1", "ZO": "2", "MEU": "3" }
print int ( ''.join ( map (lambda x: CVT[x], sys.argv[1].upper().split()) ), 4 )
