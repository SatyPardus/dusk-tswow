/*
 * Copyright (C) 2024 tswow <https://github.com/tswow/>
 * and Duskhaven <https://github.com/orgs/Duskhaven-Reforged>
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/* tslint:disable */
import { float, int, uint } from '../../data/primitives'
import { Relation } from '../../data/query/Relations'
import { PrimaryKey } from '../../data/table/PrimaryKey'
import { DBCKeyCell, DBCUIntCell } from '../../data/dbc/DBCCell'
import { CDBCFile } from './CDBCFile'
import { DBCRow } from '../../data/dbc/DBCRow'

/**
 * Main row definition
 * - Add column comments to the commented getters below
 * - Add file comments to DBCFiles.ts
 */
export class OcclusionVolumePointRow extends DBCRow<OcclusionVolumePointCreator,OcclusionVolumePointQuery> {
    /**
     * Primary Key
     *
     * Id
     */
    @PrimaryKey()
    get ID() { return new DBCKeyCell(this,this.buffer,this.offset+0) }

    /**
     * Map ID, from OcclusionVolume.cdbc
     */
    get OcclusionVolumeID() { return new DBCUIntCell(this,this.buffer,this.offset+4) }

    /**
     * Position x, client coordinates
     */
    get PositionX() { return new DBCUIntCell(this,this.buffer,this.offset+8) }

    /**
     * Position y, client coordinates
     */
    get PositionY() { return new DBCUIntCell(this,this.buffer,this.offset+12) }

    /**
     * Position Z, client coordinates
     */
    get PositionZ() { return new DBCUIntCell(this, this.buffer, this.offset + 16) }

    /**
     * Creates a clone of this row with new primary keys.
     *
     * Cloned rows are automatically added at the end of the DBC file.
     */
    clone(ID : int, c? : OcclusionVolumePointCreator) : this {
        return this.cloneInternal([ID],c);
    }
}

/**
 * Used for object creation (Don't comment these)
 */
export type OcclusionVolumePointCreator = {
    OcclusionVolumeID?: uint
    PositionX?: float
    PositionY?: float
    PositionZ?: uint
}

/**
 * Used for queries (Don't comment these)
 */
export type OcclusionVolumePointQuery = {
    ID? : Relation<int>
    OcclusionVolumeID? : Relation<uint>
    PositionX? : Relation<float>
    PositionY? : Relation<float>
    PositionZ? : Relation<uint>
}

/**
 * Table definition (specifies arguments to 'add' function)
 * - Add file comments to DBCFiles.ts
 */
export class OcclusionVolumePointCDBCFile extends CDBCFile<
    OcclusionVolumePointCreator,
    OcclusionVolumePointQuery,
    OcclusionVolumePointRow> {
    protected defaultRow = [1, 1, 0.0, 0.0, 1];

    constructor() {
        super('OcclusionVolumePoint',(t,b,o)=> new OcclusionVolumePointRow(t,b,o))
    }
    /** Loads a new OcclusionVolumePoint.dbc from a file. */
    static read(path: string): OcclusionVolumePointCDBCFile {
        return new OcclusionVolumePointCDBCFile().read(path)
    }
    add(ID : int, c? : OcclusionVolumePointCreator) : OcclusionVolumePointRow {
        return this.makeRow(0).clone(ID,c)
    }
    findByID(id : number) {
        return this.fastSearch(id);
    }
}
