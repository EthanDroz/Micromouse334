use image::{self, open};
use std::fs::File;
use std::io::{BufWriter, Write};



fn main() {

    // Preprocessing the png of the maze to a raw pixel data.
    let maze = open("./12x12orth_maze.png").expect("Failed to load maze.");
    let maze = maze.into_luma8();
    let width = maze.width();
    let height = maze.height();
    let pixels: Vec<u8> = maze.into_raw();

    // Write the raw pixel data to a 2x2 matrix.
    let mut matrix = vec![vec![0; width as usize]; height as usize];
    for (i, pixel) in pixels.iter().enumerate() {
        let y = i / width as usize;
        let x = i % width as usize;
        matrix[y][x] = *pixel;
    }

    // Create a temp buffer for the processed maze. 
    let file = File::create("./maze_matrix.txt").unwrap();
    let mut writer = BufWriter::new(file);

    // Iterates over each value in the matrix as a unsigned int.
    for row in &matrix {
        for (j, &value) in row.iter().enumerate() {
            if j > 0 {
                write!(writer, ", ").unwrap();
            }
            write!(writer, "{}", value).unwrap();
        }
        writeln!(writer).unwrap();
    }



}
