use std::{fs::read_to_string, time::Instant};

fn check_right(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(x < matrix[y].len() - 3) { return false; }

    if matrix[y][x + 1] != 'M' { return false; }
    if matrix[y][x + 2] != 'A' { return false; }
    if matrix[y][x + 3] != 'S' { return false; }

    true
}

fn check_left(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(3 <= x) { return false; }

    if matrix[y][x - 1] != 'M' { return false; }
    if matrix[y][x - 2] != 'A' { return false; }
    if matrix[y][x - 3] != 'S' { return false; }

    true
}

fn check_down(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(y < matrix.len() - 3) { return false; }

    if matrix[y + 1][x] != 'M' { return false; }
    if matrix[y + 2][x] != 'A' { return false; }
    if matrix[y + 3][x] != 'S' { return false; }

    true
}

fn check_up(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(3 <= y) { return false; }

    if matrix[y - 1][x] != 'M' { return false; }
    if matrix[y - 2][x] != 'A' { return false; }
    if matrix[y - 3][x] != 'S' { return false; }

    true
}

fn check_right_down(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(y < matrix.len() - 3) { return false; }
    if !(x < matrix[y].len() - 3) { return false; }

    if matrix[y + 1][x + 1] != 'M' { return false; }
    if matrix[y + 2][x + 2] != 'A' { return false; }
    if matrix[y + 3][x + 3] != 'S' { return false; }

    true
}

fn check_right_up(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(3 <= y) { return false; }
    if !(x < matrix[y].len() - 3) { return false; }

    if matrix[y - 1][x + 1] != 'M' { return false; }
    if matrix[y - 2][x + 2] != 'A' { return false; }
    if matrix[y - 3][x + 3] != 'S' { return false; }

    true
}

fn check_left_down(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(y < matrix.len() - 3) { return false; }
    if !(3 <= x) { return false; }

    if matrix[y + 1][x - 1] != 'M' { return false; }
    if matrix[y + 2][x - 2] != 'A' { return false; }
    if matrix[y + 3][x - 3] != 'S' { return false; }

    true
}

fn check_left_up(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(3 <= y) { return false; }
    if !(3 <= x) { return false; }

    if matrix[y - 1][x - 1] != 'M' { return false; }
    if matrix[y - 2][x - 2] != 'A' { return false; }
    if matrix[y - 3][x - 3] != 'S' { return false; }

    true
}

fn task1(input: String) -> u32 {
    // map input to a matrx
    let matrix: Vec<Vec<char>> = input.lines().map(|l| l.chars().collect()).collect();

    let mut count = 0;

    for (y, line) in matrix.iter().enumerate() {
        for (x, element) in line.iter().enumerate() {
            if *element != 'X' { continue; }

            // we have found a potential start of XMAS
            // check horizontal words
            if check_right(&matrix, y, x) { count += 1; }
            if check_left(&matrix, y, x) { count += 1; }
            // check vertical words
            if check_down(&matrix, y, x) { count += 1; }
            if check_up(&matrix, y, x) { count += 1; }
            // check diagonal words
            if check_right_down(&matrix, y, x) { count += 1; }
            if check_right_up(&matrix, y, x) { count += 1; }
            if check_left_down(&matrix, y, x) { count += 1; }
            if check_left_up(&matrix, y, x) { count += 1; }
        }
    }

    count
}

fn check_box_right(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(1 <= y && y < matrix.len() - 1) { return false; }
    if !(1 <= x && x < matrix[y].len() - 1) { return false; }

    // check M
    if matrix[y - 1][x - 1] != 'M' { return false; }
    if matrix[y + 1][x - 1] != 'M' { return false; }
    // check S
    if matrix[y - 1][x + 1] != 'S' { return false; }
    if matrix[y + 1][x + 1] != 'S' { return false; }

    true
}

fn check_box_left(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(1 <= y && y < matrix.len() - 1) { return false; }
    if !(1 <= x && x < matrix[y].len() - 1) { return false; }

    // check M
    if matrix[y - 1][x + 1] != 'M' { return false; }
    if matrix[y + 1][x + 1] != 'M' { return false; }
    // check S
    if matrix[y - 1][x - 1] != 'S' { return false; }
    if matrix[y + 1][x - 1] != 'S' { return false; }

    true
}

fn check_box_down(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(1 <= y && y < matrix.len() - 1) { return false; }
    if !(1 <= x && x < matrix[y].len() - 1) { return false; }

    // check M
    if matrix[y - 1][x - 1] != 'M' { return false; }
    if matrix[y - 1][x + 1] != 'M' { return false; }
    // check S
    if matrix[y + 1][x - 1] != 'S' { return false; }
    if matrix[y + 1][x + 1] != 'S' { return false; }

    true
}

fn check_box_up(matrix: &Vec<Vec<char>>, y: usize, x: usize) -> bool {
    if !(1 <= y && y < matrix.len() - 1) { return false; }
    if !(1 <= x && x < matrix[y].len() - 1) { return false; }

    // check M
    if matrix[y + 1][x - 1] != 'M' { return false; }
    if matrix[y + 1][x + 1] != 'M' { return false; }
    // check S
    if matrix[y - 1][x - 1] != 'S' { return false; }
    if matrix[y - 1][x + 1] != 'S' { return false; }

    true
}

fn task2(input: String) -> u32 {
    // map input to a matrx
    let matrix: Vec<Vec<char>> = input.lines().map(|l| l.chars().collect()).collect();

    let mut count = 0;

    for (y, line) in matrix.iter().enumerate() {
        for (x, element) in line.iter().enumerate() {
            if *element != 'A' { continue; }

            // we have found a potential middle of MAS
            // check words
            if check_box_right(&matrix, y, x) { count += 1; }
            if check_box_left(&matrix, y, x) { count += 1; }
            if check_box_down(&matrix, y, x) { count += 1; }
            if check_box_up(&matrix, y, x) { count += 1; }
        }
    }

    count
}

fn main() {
    let input = read_to_string("input.task").unwrap();
    let input2 = input.clone();

    let instant_start = Instant::now();
    let count = task1(input);
    let instant_end = Instant::now();

    println!("XMAS count: {}", count);
    println!("time: {} microseconds", instant_end.duration_since(instant_start).as_micros());

    let instant_start = Instant::now();
    let count = task2(input2);
    let instant_end = Instant::now();

    println!("X-MAS count: {}", count);
    println!("time: {} microseconds", instant_end.duration_since(instant_start).as_micros());
}
