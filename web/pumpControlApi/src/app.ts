import express, { Request, Response } from 'express';
import path from 'path';
import { SerialPort } from 'serialport';
import { urlencoded } from 'body-parser';
const port = process.env.PORT ?? 3000;
const serialPath = process.env.SERIAL_PORT_PATH??'COM3';
const baudRate = parseInt(process.env.BAUD_RATE??'9600');

const serialport = new SerialPort({
    path: serialPath,
    baudRate
});

const app = express();

app.use(express.json());
app.use(urlencoded({extended: true}));

app.post('/execute', (req: Request, res: Response) => {
    const {pumpId, durationMs} = req.body;

    if((!pumpId && pumpId != 0) || (!durationMs && durationMs != 0)) {
        console.error(`Invalid execute request, request: ${JSON.stringify(req.body)}`);
        res.status(400).send();
        return;
    }

    try {
        const command = JSON.stringify({
            pid: pumpId,
            dms: durationMs
    });

        console.log(`Executing command: ${command}`);
        serialport.write(`${command}\n`, 'ascii');

        console.info('Command written successfully');
        res.status(200).send({
            message: 'Command written successfully'
        });

    } catch(e) {
        console.error(`Error on executing serial command, execption: ${e}`);
    }


})

app.use(express.static(path.join(__dirname, '../public')));

console.log(`Public path: ${path.join(__dirname, '../public')}`);

app.listen(port, () => {
    console.log(`server started at http://localhost:${port}`);
});