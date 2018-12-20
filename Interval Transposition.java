package com.company;

import java.util.*;
import java.io.*;

public class Main {

    private static char note;
    private static int octave;

    public static void main(String[] args) throws IOException {

        //Reads the file
        Scanner scan = new Scanner(new File("gleb.dat"));

        char[] scale = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
        int l = scale.length;

        while (scan.hasNextLine()) {

            String full = scan.nextLine();
            Scanner bb = new Scanner(full);
            bb.useDelimiter("");

            //Records the initial note and its octave
            note = bb.next().charAt(0);
            octave = Integer.parseInt(bb.next());
            bb.useDelimiter(" ");

            System.out.print(note + "" + octave + " ");

            while (bb.hasNext()) {

                //Searches for the index of note, stored in oIndx
                int oIndx = -1;
                int indx = 0;
                for (char c : scale) {
                    if (note == c)
                        oIndx = indx;
                    indx++;
                }

                int interval = bb.nextInt();

                addInterval(interval, oIndx, l);

                System.out.print(note + "" + octave + " ");
            }

            System.out.println();
        }
    }

    /**
     * Simply adds the interval to the note and formats accordingly
     * Accounts for octave changes
     *
     * @param intrvl    the interval to be added to note
     * @param oIndx     the initial index of the current note
     * @param length    the length of scale array
     */
    private static void addInterval(int intrvl, int oIndx, int length){

        //Adds the interval to note, and tests if note is in a new octave
        if (intrvl != 0) {
            if (intrvl > 0) {
                note += intrvl - 1;
                if (oIndx + intrvl > length)
                    octave++;
            } else {
                note += intrvl + 1;
                if (oIndx + intrvl + 1 < 0)
                    octave--;
            }

            //Simply assures that note is an actual note character
            if (note < 'A')
                note = (char) (('G' + 1) - ('A' - note));
            else if (note > 'G')
                note = (char) (('A' - 1) + (note - 'G'));
        }

    }
}
