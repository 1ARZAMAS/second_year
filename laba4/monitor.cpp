/*
Монитор - высокоуровневый механизм синхронизации процессов, 
обеспечивающий доступ к разделяемым ресурсам.При 
многозадачности, основанной на мониторах, компилятор или 
интерпретатор прозрачно для программиста вставляет код блокировки-
разблокировки в оформленные соответствующим образом процедуры,
избавляя программиста от явного обращения к примитивам синхронизации.
Монитор состоит из:
1. набора процедур, взаимодействующих с общим ресурсом
2. мьютекса
3. переменных, связанных с этим ресурсом
4. инварианта, который определяет условия, позволяющие избежать 
состояние гонки
*/