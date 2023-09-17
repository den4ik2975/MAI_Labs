#!bin/bash
#Создадим папку и перейдем в нее
mkdir laboratoryWork
cd laboratoryWork/

# Теперь создадим файлы index и logs
touch index logs

# Сделаем небольшое форматирование для индекса и посмторим что получилось
{ pwd; echo; echo "Files:"; } >> index
cat index

# Добавим в индекс файл логс и посмотрим что получилось
stat -c "%n - %sb (%U)" logs >> index
cat index

# Добавляем наши действия в логи и опять посмотрим
echo "$(whoami) - Created and formated index" >> logs
echo "$(whoami) - Created logs and added it to index" >> logs
cat logs

# Создаем файлы animals food tickets и добаляем их в индекс
touch animals food tickets
stat -c "%n - %sb (%U)" animals >> index
stat -c "%n - %sb (%U)" food >> index
stat -c "%n - %sb (%U)" tickets >> index

# Добавляем логи
echo "$(whoami) - Created animals food tickets" >> logs

# Заполняем животных
echo "Dog
Elephant
Giraffe
Lion
Elephant
Dog
Cat
Cat
Dog" >> animals

# Так как размер файла с животными изменился, нужно измениь его и в индексе
# Удаляем старую запись о файле
grep -v "animals" index > temp && mv temp index

# Добаляем обновленную информацию в начало списка файлов и проверим
{ head -n 3 index; echo "$(stat -c "%n - %sb (%U)" animals)"; tail -n +4 index; } > temp && mv temp index
cat index

# Логи
echo "$(whoami) - Added animals food tickets to index" >> logs
echo "$(whoami) - Edited animals" >> logs
echo "$(whoami) - Updated info about animals in index" >> logs

# Удаляем всех собак и сортируем файл
cat animals | grep -v Dog | sort > temp && mv temp animals

# Опять обновим инфу о файле 
grep -v "animals" index > temp && mv temp index
{ head -n 3 index; echo "$(stat -c "%n - %sb (%U)" animals)"; tail -n +4 index; } > temp && mv temp index

# И снова добавляем логи 
echo "$(whoami) - Edited animals" >> logs
echo "$(whoami) - Updated info about animals in index" >> logs

# Файл с едой вдруг стал не нужен, удаляем его и не забываем про индекс
rm food
ls
grep -v "food" index > temp && mv temp index

# И снова добавляем логи 
echo "$(whoami) - Deleted food file" >> logs
echo "$(whoami) - Deleted food from index" >> logs

# Заполним файл с ценами
echo "Child - 500$
Man - 228$
Woman - 230$
Family - 2$" >> tickets

# Снова обновим инфу
grep -v "tickets" index > temp && mv temp index
{ head -n 3 index; echo "$(stat -c "%n - %sb (%U)" tickets)"; tail -n +4 index; } > temp && mv temp index

# И снова добавляем логи 
echo "$(whoami) - Updated info in index" >> logs

# Но ведь размер логов тоже меняется, обновим их тоже
grep -v "logs" index > temp && mv temp index
{ head -n 3 index; echo "$(stat -c "%n - %sb (%U)" logs)"; tail -n +4 index; } > temp && mv temp index

# Ну и наконец отсортируем файлы в индеске 
head -n 3 index > temp && tail -n +4 index | sort >> temp && mv temp index

# Посмотрим что в итоге получилось
cat index
echo
cat logs
