
clang++-3.5 -c simple.cpp -Xclang -analyze \
                      -Xclang -analyzer-output=text \
                      -Xclang -load \
                      -Xclang /home/shyam/servicetask/SASbuild/lib/libSas.so \
                      -Xclang -analyzer-checker=sas.Example.NameSpace \
                     # -Xclang -analyzer-checker=sas.Example.QualifierName \
                      #-Xclang -analyzer-checker=sas.Example.Code \
                     # -Xclang -analyzer-checker=sas.Example.String \
                     # -Xclang -analyzer-checker=sas.ThreadSafety.GlobalStatic \
                     # -Xclang -analyzer-checker=core.DivideZero \
                      

