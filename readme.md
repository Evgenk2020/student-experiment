# Statistical analysis of variance

Lab utility for statistical analysis of variance. It is designed for data treatment containing more than two different variants with some overlapping. To evaluate confidence interval the Student t criteria at a rank of 0.05 is using by default. It may be changed to another one depending of precision tolerance.

Run it with specified keys

```

st-exp [-d | -df] [data one] [data two] ... [final data]
st-exp [-d | -df] [data one] [data two] ... [final data] alf [0..1]
st-exp [-d | -df] [series one ([data one] [data two])] -- [series two] -- ... [final series]
st-exp [-d | -df] [series one ([data one] [data two])] -- [series two] -- ... [final series] alf [0..1]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/img/screen.png)

Use `build.sh` and `run.sh` to compile and run the application

For more convenience you may add path to the application into `.bashrc` file

```

export PATH=$PATH:/%path_to_application_folder%/

```

and then use simple SH schemes e.g.

```SH

#!/bin/bash

st-exp -d 2.3 3.4 2.6 3.5
echo "----------------"
st-exp -d 2.5 3.4 2.6 -- 8.9 11.2 13.5
echo "----------------"
st-exp -d 2.3 3.4 2.6 3.5 alf 0.01
echo "----------------"
st-exp -d 2.5 3.4 2.6 -- 8.9 11.2 13.5 alf 0.2

exec $SHELL

```

or for writing `.csv` file use

```SH

#!/bin/bash

st-exp -df 2.3 3.4 2.6 3.5
echo "----------------"
st-exp -df 2.5 3.4 2.6 -- 8.9 11.2 13.5
echo "----------------"
st-exp -df 2.3 3.4 2.6 3.5 alf 0.01
echo "----------------"
st-exp -df 2.5 3.4 2.6 -- 8.9 11.2 13.5 alf 0.2

exec $SHELL

```
