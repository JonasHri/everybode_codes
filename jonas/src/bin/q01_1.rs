use std::error::Error;
use std::fs;

fn main() -> Result<(), Box<dyn Error>> {
    let message: String = fs::read_to_string("1.txt")?;
    println!("{}", message);
    let mut sum = 0;
    for letter in message.chars() {
        if letter == 'B' {
            sum += 1;
        }
        if letter == 'C' {
            sum += 3;
        }
    }

    println!("{}", sum);
    Ok(())
}
