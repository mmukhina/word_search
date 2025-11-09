### Постановка задачи
Реализовать алгоритм поиска информации по запросу среди указанного множества документов при помощи алгоритма префиксного дерева.
Входные данные для алгоритма: текстовый запрос произвольного формата, префиксное дерево составляется на основе множества текстовых документов, хранение которых организовано в текстовых файлах. Уникальный идентификатор документа - имя файла с документом. Атомарная единица - слово. Необходимо учесть наличие знаков препинания и пунктуации.
Выходные данные: на экран или в текстовый файл должен выводиться список уникальных идентификаторов документов и к каждому идентификатору вывести все совпадения с запросом в формате (номер строки, совпадение и 10 последующих слов). 
Язык программирования - C++, запрещается использовать регулярные выражения, а также любые СУБД и прочие средства работы с базами данных.


### Компиляция
```
make run
```

### Работа программы:

Главное меню

<img width="593" height="171" alt="Screenshot 2025-11-06 at 15 04 21" src="https://github.com/user-attachments/assets/42d4aa1f-114c-4492-8074-0bf920a041e2" />

<br><br>
Если список документов пуст, поиск документов и удаление нельзя бдует осуществить

<img width="625" height="180" alt="Screenshot 2025-11-06 at 15 22 58" src="https://github.com/user-attachments/assets/1517f0e8-57af-4413-9cd7-84ba1e258c6e" />
<img width="278" height="106" alt="Screenshot 2025-11-06 at 15 23 44" src="https://github.com/user-attachments/assets/38afbd4c-783b-4417-a5a8-318743b7c6dd" />
<br>
<img width="311" height="124" alt="Screenshot 2025-11-06 at 15 24 51" src="https://github.com/user-attachments/assets/8efc1d38-34ec-40dc-9758-d86876e7c462" />
<img width="328" height="112" alt="Screenshot 2025-11-06 at 15 25 02" src="https://github.com/user-attachments/assets/3124bf94-85da-4289-a637-a225e18d59e4" />

<br><br>
Добавление документа в список для поиска

<img width="463" height="72" alt="Screenshot 2025-11-06 at 15 07 10" src="https://github.com/user-attachments/assets/dfeb3ac4-e09e-4288-9a33-c92db6a1bdc1" />
<br>
<img width="401" height="148" alt="Screenshot 2025-11-06 at 15 07 22" src="https://github.com/user-attachments/assets/6f271a26-536b-4861-afc7-f87918f8053c" />

<br><br>
Просмотр всех вайлов в которых будет происходит поиск слова

<img width="411" height="143" alt="Screenshot 2025-11-06 at 15 07 52" src="https://github.com/user-attachments/assets/6353920e-1b83-45a3-8740-48eb1c851f98" />
<br>
<img width="248" height="168" alt="Screenshot 2025-11-06 at 15 08 23" src="https://github.com/user-attachments/assets/35ae2dc9-d25c-41bd-a345-51f7c21c1019" />

<br><br>
Поиск слова в документах из списка

<img width="265" height="127" alt="Screenshot 2025-11-09 at 14 57 08" src="https://github.com/user-attachments/assets/3d3f8d70-3b7b-4b92-aaf8-0af29e928aac" />
<br>
<img width="222" height="93" alt="Screenshot 2025-11-09 at 14 55 24" src="https://github.com/user-attachments/assets/130de0c1-54be-4805-b08d-6255bcbb3d9f" />
<br>
<img width="388" height="240" alt="Screenshot 2025-11-09 at 14 55 42" src="https://github.com/user-attachments/assets/796a6446-1e8c-4268-b345-b91411986768" />
<br>
<img width="221" height="123" alt="Screenshot 2025-11-09 at 14 56 05" src="https://github.com/user-attachments/assets/1c6046c2-0d61-497f-a92a-37d17e6eff2b" />

<br><br>
Удалить документ из списка

<img width="281" height="114" alt="Screenshot 2025-11-06 at 15 10 05" src="https://github.com/user-attachments/assets/b6a9f4a1-777c-4ef0-8026-ac8dd4283796" />
<br>
<img width="276" height="148" alt="Screenshot 2025-11-06 at 15 10 27" src="https://github.com/user-attachments/assets/2b487ede-a580-4579-95f4-e97f5aace867" />
<br>
<img width="421" height="138" alt="Screenshot 2025-11-06 at 15 10 41" src="https://github.com/user-attachments/assets/42914087-f053-42b0-aa2f-387cbcac2b69" />
<br>
<img width="254" height="159" alt="Screenshot 2025-11-06 at 15 10 54" src="https://github.com/user-attachments/assets/7eb833a7-f0d3-4611-baba-09d31dc8a5ac" />

<br><br>
При повторном входе сохраняеться предыдущий список документов

<img width="606" height="171" alt="Screenshot 2025-11-06 at 15 11 42" src="https://github.com/user-attachments/assets/79d951c3-7baa-4263-9b86-c6cd8511dfb2" />


