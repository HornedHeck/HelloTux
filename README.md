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

## [Lab 4]("./Lab%204/")

Makefile is them main "difficulty" in this lab

You can read about make and Makefile [here](https://habr.com/ru/post/211751/)

Also converter is moved to ["morze converter"](".morze_converter/") folder, because it will be used in Lab 6

## [Lab 5]("./Lab%205/")

I use pthread to achive multythreading in this lib. This is C realisation of POSIX standart (Unix Threads).
You can read about pthread [here](https://habr.com/ru/post/326138/). Please, read this article rather than copy-paste code samples.

### Main pthread elements:

1. Creation of new thread with startup function and params
```c
pthread_create(&pid, nullptr, launch, (void *) &path);
```

2. Creation of mutexes
```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t address_lock = PTHREAD_MUTEX_INITIALIZER;
```

3. Usage of mutexes
```c
pthread_mutex_lock(&address_lock);
//....
pthread_mutex_unlock(&address_lock);
//....
pthread_mutex_lock(&lock);
res_file.open(res_path , std::ios::app | std::ios::out);
res_file << res << std::endl;
pthread_mutex_unlock(&lock);
```
"address_lock" mutex let calculation thread to read file content properly.
"lock" mutex is required to results output syncronization.

4. Waiting for all calculation threads
```c
for (auto pid : pid_list) {
    pthread_join(pid, &res);
}
```
