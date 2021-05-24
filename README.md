# Биллинговая база оператора связи
Описание задания
 Метод сортировки
 Сортировка прямым обменом (метод «пузырька»)
 Биллинговая база оператора связи
    Система управления информацией о клиентах,
    оказываемых им услугах и об оплате услуг.Поддерживаемые данные
        * Клиенты – физические лица и организации
            ** Наименование или ФИО
            ** Контакты : контактные лица, адрес(а), телефон(ы), e - mail(ы)
            ** История услуг : услуги, в какое время оказывались 
        * Услуги
            ** Наименование
            ** Характеристики : номер, группа номеров, Интернет, SMS, спец.предложения
            ** Тарифный план(какая часть услуги в какое время сколько будет стоить)
        * Счета клиентов
            ** Баланс
            ** Поступления на счет
            ** Списания за оказание услуг связи
            * Ограничения : размер максимального кредита и сроки его погашения Поддерживаемые операции
        * Получение списка клиентов, в т.ч.по оказываемым услугам в заданном интервале времени, по характеристикам их счетов
        * Добавление и удаление данных о клиенте, чтение и редактирование данных о нем
        * Добавление и удаление услуги, чтение и редактирование данных о ней 
## NB! 
Для хранения и обработки данных используется SQLite3. Для успешной компиляции кода необходимо установить пакет 
https://www.sqlite.org/download.html#amalgtarball
Для успешной сборки программы необходимо указать ключи -lm -lsqlite3, например: 
gcc -g /path/to/file/pz2.c -o /path/to/file/pz2 -lm -lsqlite3 
