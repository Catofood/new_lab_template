// Шаблон record типа C#
namespace Lab;

/// <summary>
/// Запись студента
/// </summary>
/// <param name="Name">Имя студента</param>
/// <param name="Age">Возраст</param>
/// <param name="Grade">Оценка</param>
public record Student(string Name, int Age, double Grade)
{
    /// <summary>
    /// Проверяет, является ли студент отличником
    /// </summary>
    public bool IsExcellent => Grade >= 4.5;
}
