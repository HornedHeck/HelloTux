# HelloTux
OSIS 3.3 labs

## [Lab 1]("./Lab%201/")
 
Everything is discribed in man:
```bash
man ps
```

## [Lab 2]("./Lab%202/")
```bash
man tput
man date
```

## [Lab 3]("./Lab%203/")

[content](./Lab%203/content) &ndash; example input file

[Simple bash arrays tutorial](https://www.javatpoint.com/bash-arrays)



### Main parts

1. Read file line by line:
```bash
while read line
    do
    lines+=("$line")
    done < $1
```

2. Move 2 rows from lines to separate variables (table name and list of columns)
```bash
table=${lines[0]}
fields=${lines[1]}

lines=("${lines[@]:2}")
```

3. Get last index
```bash
l_i=$((${#lines[*]}-1))
```

4. Print result
```bash
echo "INSERT INTO $table"
echo "VALUES ($fields)"
for vi in ${!lines[*]}
    do
    if [[ $vi != $l_i ]]
        then
        echo "(${lines[$vi]}),"
        else
        echo "(${lines[$vi]});"    
    fi
    done
```



