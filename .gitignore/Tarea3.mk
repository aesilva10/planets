Resultados_hw3.pdf: Onda.py
    python Onda.py
orbitas_planetas.png: plots_planetas.py
    python plots_planetas.py
plots_planetas.py: datosx.txt datosy.txt datosz.txt
    python plots_planetas.py
datosx.txt: planetas.x
    ./planetas.x
planetas.x : Planetas.c
cc Planetas.c -o planetas.x
