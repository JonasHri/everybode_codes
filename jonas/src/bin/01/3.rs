use std::error::Error;
use std::fs;

fn main() -> Result<(), Box<dyn Error>> {
    let message: String = fs::read_to_string("3.txt")?;
    println!("{}", message);
    let mut sum: i32 = 0;
    let chars: Vec<char> = message.chars().collect();
    for i in (0..chars.len()).step_by(3) {
        let mut enemy_count: i32 = 3;
        for enemy in &chars[i..i + 3] {
            if *enemy == 'x' {
                enemy_count -= 1;
            }
            sum += match enemy {
                'B' => 1,
                'C' => 3,
                'D' => 5,
                _ => 0,
            }
        }
        sum += enemy_count * (enemy_count - 1);
    }

    println!("{}", sum);
    Ok(())
}
